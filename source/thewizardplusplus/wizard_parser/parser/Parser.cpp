#include "Parser.h"
#include "exceptions/ParseException.h"
#include <numeric>
#include <algorithm>

using namespace thewizardplusplus::wizard_parser::node;
using namespace thewizardplusplus::wizard_parser::parser::exceptions;

namespace thewizardplusplus {
namespace wizard_parser {
namespace parser {

const auto separator_parser = dummy();

void assign(const Parser& parser1, const Parser& parser2) {
	*parser1.get() = *parser2.get();
}

Parser copy(const Parser& parser) {
	const auto parser_copy = dummy();
	assign(parser_copy, parser);

	return parser_copy;
}

Parser separation(const Parser& separator, const Parser& parser) {
	return std::make_shared<ParserFunction>(
		[=] (const std::string& text, const size_t position) -> Result {
			const auto old_separator_copy = copy(separator_parser);

			assign(separator_parser, separator);
			const auto result = parser->operator()(text, position);
			assign(separator_parser, old_separator_copy);

			return result;
		}
	);
}

Parser disable_separation(const Parser& parser) {
	return separation(nothing(), parser);
}

Parser hide(const Parser& parser) {
	return std::make_shared<ParserFunction>(
		[=] (const std::string& text, const size_t position) -> Result {
			const auto result = parser->operator()(text, position);
			return std::get<0>(result)
				? Result{true, Node(), std::get<2>(result)}
				: Result{false, Node(), std::get<2>(result)};
		}
	);
}

Parser name(const std::string& name, const Parser& parser) {
	return std::make_shared<ParserFunction>(
		[=] (const std::string& text, const size_t position) -> Result {
			const auto result = parser->operator()(text, position);
			return std::get<0>(result)
				? Result{
					true,
					{name, "", {std::get<1>(result)}},
					std::get<2>(result)
				}
				: Result{false, Node(), std::get<2>(result)};
		}
	);
}

Parser leaves(const Parser& parser) {
	return std::make_shared<ParserFunction>(
		[=] (const std::string& text, const size_t position) -> Result {
			const auto result = parser->operator()(text, position);
			return std::get<0>(result)
				? Result{
					true,
					{
						std::get<1>(result).name,
						std::get<1>(result).value,
						leaves(std::get<1>(result))
					},
					std::get<2>(result)
				}
				: Result{false, Node(), std::get<2>(result)};
		}
	);
}

Parser lexeme(const Parser& parser) {
	return std::make_shared<ParserFunction>(
		[=] (const std::string& text, const size_t position) -> Result {
			const auto result = leaves(parser)->operator()(text, position);
			return std::get<0>(result)
				? Result{
					true,
					{
						std::get<1>(result).name,
						std::accumulate(
							std::get<1>(result).children.begin(),
							std::get<1>(result).children.end(),
							std::string(),
							[] (const std::string& value, const Node& child) {
								return value + child.value;
							}
						),
						{}
					},
					std::get<2>(result)
				}
				: Result{false, Node(), std::get<2>(result)};
		}
	);
}

Parser operator>>(const Parser& parser1, const Parser& parser2) {
	const auto separator_parser = separator();
	return std::make_shared<ParserFunction>(
		[=] (const std::string& text, const size_t position) -> Result {
			auto nodes = NodeGroup();

			const auto result1 = parser1->operator()(text, position);
			if (!std::get<0>(result1)) {
				return Result{false, Node(), std::get<2>(result1)};
			}
			nodes.push_back(std::get<1>(result1));

			const auto separator_result = separator_parser->operator()(
				text,
				std::get<2>(result1)
			);
			if (!std::get<0>(separator_result)) {
				return Result{false, Node(), std::get<2>(separator_result)};
			}
			nodes.push_back(std::get<1>(separator_result));

			const auto result2 = parser2->operator()(
				text,
				std::get<2>(separator_result)
			);
			if (!std::get<0>(result2)) {
				return Result{false, Node(), std::get<2>(result2)};
			}
			nodes.push_back(std::get<1>(result2));

			return Result{true, Node{"", "", nodes}, std::get<2>(result2)};
		}
	);
}

Parser operator|(const Parser& parser1, const Parser& parser2) {
	return std::make_shared<ParserFunction>(
		[=] (const std::string& text, const size_t position) -> Result {
			const auto result1 = parser1->operator()(text, position);
			const auto result2 = parser2->operator()(text, position);

			if (std::get<0>(result1) && !std::get<0>(result2)) {
				return result1;
			} else if (!std::get<0>(result1) && std::get<0>(result2)) {
				return result2;
			} else if (std::get<0>(result1) && std::get<0>(result2)) {
				if (std::get<2>(result1) >= std::get<2>(result2)) {
					return result1;
				} else {
					return result2;
				}
			} else {
				return Result{
					false,
					Node(),
					std::min(std::get<2>(result1), std::get<2>(result2))
				};
			}
		}
	);
}

Parser operator!(const Parser& parser) {
	return parser | nothing();
}

Parser operator*(const Parser& parser) {
	const auto separator_parser = separator();
	return std::make_shared<ParserFunction>(
		[=] (const std::string& text, const size_t position) -> Result {
			auto nodes = NodeGroup();
			auto old_end_position = position;
			auto end_position = position;
			auto not_first = false;
			while (true) {
				if (not_first) {
					const auto separator_result = separator_parser->operator()(
						text,
						end_position
					);
					if (!std::get<0>(separator_result)) {
						break;
					}
					nodes.push_back(std::get<1>(separator_result));

					old_end_position = end_position;
					end_position = std::get<2>(separator_result);
				}

				const auto result = parser->operator()(text, end_position);
				if (!std::get<0>(result)) {
					if (not_first) {
						nodes.pop_back();
						end_position = old_end_position;
					}

					break;
				}
				nodes.push_back(std::get<1>(result));
				end_position = std::get<2>(result);

				not_first = true;
			}

			return Result{true, {"", "", nodes}, end_position};
		}
	);
}

Parser operator+(const Parser& parser) {
	return parser >> *parser;
}

Parser operator-(const Parser& parser1, const Parser& parser2) {
	return std::make_shared<ParserFunction>(
		[=] (const std::string& text, const size_t position) -> Result {
			const auto result = parser1->operator()(text, position);
			return
				std::get<0>(result)
				&& !std::get<0>(parser2->operator()(text, position))
					? result
					: Result{false, Node(), std::get<2>(result)};
		}
	);
}

Parser list(const Parser& parser, const Parser& separator) {
	return parser >> *(separator >> parser);
}

Parser dummy(void) {
	return std::make_shared<ParserFunction>(
		[=] (const std::string& text, const size_t position) -> Result {
			(void)text;
			return Result{true, Node(), position};
		}
	);
}

Parser nothing(void) {
	static const auto nothing_parser = dummy();
	return nothing_parser;
}

Parser boundary(void) {
	static const auto word_parser = word();
	static const auto boundary_parser = std::make_shared<ParserFunction>(
		[=] (const std::string& text, const size_t position) -> Result {
			const auto result_before =
				position != 0
					? word_parser->operator()(text, position - 1)
					: Result();
			const auto result = word_parser->operator()(text, position);

			return
				(!std::get<0>(result_before) && std::get<0>(result))
				|| (std::get<0>(result_before) && !std::get<0>(result))
					? Result{true, Node(), position}
					: Result{false, Node(), position};
		}
	);

	return boundary_parser;
}

Parser separator(void) {
	static const auto separator_parser_wrapper = std::make_shared<
		ParserFunction
	>(
		[=] (const std::string& text, const size_t position) -> Result {
			return separator_parser->operator()(text, position);
		}
	);

	return separator_parser_wrapper;
}

Parser end(void) {
	static const auto end_parser = std::make_shared<ParserFunction>(
		[=] (const std::string& text, const size_t position) -> Result {
			return position == text.size()
				? Result{true, Node(), position}
				: Result{false, Node(), position};
		}
	);

	return end_parser;
}

Parser operator"" _s(const char symbol) {
	return std::make_shared<ParserFunction>(
		[=] (const std::string& text, const size_t position) -> Result {
			return position < text.size() && text[position] == symbol
				? Result{
					true,
					Node{"", std::string(1, symbol), {}},
					position + 1
				}
				: Result{false, Node(), position + 1};
		}
	);
}

Parser operator"" _t(const char* text, const size_t length) {
	return lexeme(
		disable_separation(
			std::accumulate(
				text,
				text + length,
				dummy(),
				[] (const Parser& parser, const char symbol) {
					return parser >> operator"" _s(symbol);
				}
			)
		)
	);
}

Parser any(void) {
	static const auto any_parser = std::make_shared<ParserFunction>(
		[=] (const std::string& text, const size_t position) -> Result {
			return position < text.size()
				? Result{
					true,
					Node{"", std::string(1, text[position]), {}},
					position + 1
				}
				: Result{false, Node(), position + 1};
		}
	);

	return any_parser;
}

Parser any(const std::string& symbols) {
	if (symbols.empty()) {
		throw std::invalid_argument("any() at empty string");
	}

	return std::accumulate(
		symbols.begin() + 1,
		symbols.end(),
		operator"" _s(symbols[0]),
		[] (const Parser& parser, const char symbol) {
			return parser | operator"" _s(symbol);
		}
	);
}

Parser space(void) {
	static const auto space_parser = any(" \t\n\v\f\r");
	return space_parser;
}

Parser letter(void) {
	static const auto letter_parser = any(
		"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"
	);

	return letter_parser;
}

Parser digit(void) {
	static const auto digit_parser = any("0123456789");
	return digit_parser;
}

Parser word(void) {
	static const auto word_parser = letter() | digit() | '_'_s;
	return word_parser;
}

Parser word(const Parser& parser) {
	static const auto boundary_parser = boundary();
	return disable_separation(boundary_parser >> parser >> boundary_parser);
}

Node simplify(
	const Node& node,
	const SimplifyLevel level,
	const StringGroup& saved
) {
	if (
		level != SimplifyLevel::EMPTIES
		&& level != SimplifyLevel::WRAPPERS
		&& level != SimplifyLevel::AST
	) {
		throw std::invalid_argument("invalid simplify level");
	}

	auto children = NodeGroup();
	std::transform(
		node.children.begin(),
		node.children.end(),
		std::back_inserter(children),
		[=] (const Node& node) {
			return simplify(node, level, saved);
		}
	);
	children.erase(
		std::remove_if(
			children.begin(),
			children.end(),
			[] (const Node& node) {
				return node.name.empty() && is_empty(node);
			}
		),
		children.end()
	);

	auto simplified_node = Node{node.name, node.value, children};
	if (simplified_node.value.empty() && simplified_node.children.size() == 1) {
		auto child = simplified_node.children.front();
		if (
			(level == SimplifyLevel::WRAPPERS && simplified_node.name.empty())
			|| (level == SimplifyLevel::AST && std::find(
				saved.begin(),
				saved.end(),
				simplified_node.name
			) == saved.end())
			|| (level != SimplifyLevel::EMPTIES && child.name.empty())
		) {
			if (child.name.empty()) {
				child.name = simplified_node.name;
			}
			simplified_node = child;
		}
	}

	return simplified_node;
}

Node parse(
	const Parser& parser,
	const std::string& text,
	const SimplifyLevel level,
	const StringGroup& saved
) {
	const auto result = parser->operator()(text, 0);
	if (!std::get<0>(result)) {
		throw ParseException(text, std::get<2>(result));
	}

	return simplify(std::get<1>(result), level, saved);
}

}
}
}
