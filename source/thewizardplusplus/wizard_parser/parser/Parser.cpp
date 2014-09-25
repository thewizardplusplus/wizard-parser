#include "Parser.h"
#include <numeric>
#include <iostream>

namespace thewizardplusplus {
namespace wizard_parser {
namespace parser {

const auto separator_parser = nothing();

void assign(const Parser& parser1, const Parser& parser2) {
	*parser1.get() = *parser2.get();
}

Parser separation(const Parser& separator, const Parser& parser) {
	return std::make_shared<ParserFunction>(
		[=] (const std::string& text, const size_t position) -> Result {
			const auto old_separator_copy = nothing();
			assign(old_separator_copy, separator_parser);

			assign(separator_parser, separator);
			const auto result = parser->operator()(text, position);
			assign(separator_parser, old_separator_copy);

			return result;
		}
	);
}

Parser hide(const Parser& parser) {
	return std::make_shared<ParserFunction>(
		[=] (const std::string& text, const size_t position) -> Result {
			const auto result = parser->operator()(text, position);
			return std::get<0>(result)
				? Result{true, node::Node(), std::get<2>(result)}
				: Result();
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
					{
						name,
						std::get<1>(result).value,
						std::get<1>(result).children
					},
					std::get<2>(result)
				}
				: Result();
		}
	);
}

Parser plain(const Parser& parser, const size_t level) {
	return std::make_shared<ParserFunction>(
		[=] (const std::string& text, const size_t position) -> Result {
			const auto result = parser->operator()(text, position);
			return std::get<0>(result)
				? Result{
					true,
					{
						std::get<1>(result).name,
						std::get<1>(result).value,
						leaves(std::get<1>(result), level)
					},
					std::get<2>(result)
				}
				: Result();
		}
	);
}

Parser lexeme(const Parser& parser) {
	return std::make_shared<ParserFunction>(
		[=] (const std::string& text, const size_t position) -> Result {
			const auto result = plain(parser)->operator()(text, position);
			return std::get<0>(result)
				? Result{
					true,
					{
						std::get<1>(result).name,
						std::accumulate(
							std::get<1>(result).children.begin(),
							std::get<1>(result).children.end(),
							std::string(),
							[] (
								const std::string& value,
								const node::Node& child
							) {
								return value + child.value;
							}
						),
						{}
					},
					std::get<2>(result)
				}
				: Result();
		}
	);
}

Parser operator>>(const Parser& parser1, const Parser& parser2) {
	const auto separator_parser = separator();
	return std::make_shared<ParserFunction>(
		[=] (const std::string& text, const size_t position) -> Result {
			auto nodes = node::NodeGroup();

			const auto result1 = parser1->operator()(text, position);
			if (!std::get<0>(result1)) {
				return Result();
			} else if (!is_empty(std::get<1>(result1))) {
				nodes.push_back(std::get<1>(result1));
			}

			const auto separator_result = separator_parser->operator()(
				text,
				std::get<2>(result1)
			);
			if (!std::get<0>(separator_result)) {
				return Result();
			}

			const auto result2 = parser2->operator()(
				text,
				std::get<2>(separator_result)
			);
			if (!std::get<0>(result2)) {
				return Result();
			} else if (!is_empty(std::get<1>(result2))) {
				nodes.push_back(std::get<1>(result2));
			}

			return Result{
				true,
				node::Node{"", "", nodes},
				std::get<2>(result2)
			};
		}
	);
}

Parser operator|(const Parser& parser1, const Parser& parser2) {
	return std::make_shared<ParserFunction>(
		[=] (const std::string& text, const size_t position) -> Result {
			const auto result = parser1->operator()(text, position);
			return std::get<0>(result)
				? result
				: parser2->operator()(text, position);
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
			auto nodes = node::NodeGroup();
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
				} else {
					not_first = true;
				}

				const auto result = parser->operator()(text, end_position);
				if (!std::get<0>(result)) {
					break;
				} else if (!is_empty(std::get<1>(result))) {
					nodes.push_back(std::get<1>(result));
				}
				end_position = std::get<2>(result);
			}

			return Result{true, {"", "", nodes}, end_position};
		}
	);
}

Parser operator+(const Parser& parser) {
	return plain(parser >> *parser);
}

Parser operator-(const Parser& parser1, const Parser& parser2) {
	return std::make_shared<ParserFunction>(
		[=] (const std::string& text, const size_t position) -> Result {
			const auto result = parser1->operator()(text, position);
			return
				std::get<0>(result)
				&& !std::get<0>(parser2->operator()(text, position))
					? result
					: Result();
		}
	);
}

Parser list(const Parser& parser, const Parser& separator) {
	return parser >> *(separator >> parser);
}

Parser nothing(void) {
	return std::make_shared<ParserFunction>(
		[=] (const std::string& text, const size_t position) -> Result {
			(void)text;
			return Result{true, node::Node(), position};
		}
	);
}

Parser boundary(void) {
	const auto word_parser = word();
	return std::make_shared<ParserFunction>(
		[=] (const std::string& text, const size_t position) -> Result {
			const auto result_before =
				position != 0
					? word_parser->operator()(text, position - 1)
					: Result();
			const auto result = word_parser->operator()(text, position);

			return
				(!std::get<0>(result_before) && std::get<0>(result))
				|| (std::get<0>(result_before) && !std::get<0>(result))
					? Result{true, node::Node(), position}
					: Result();
		}
	);
}

Parser separator(void) {
	return std::make_shared<ParserFunction>(
		[=] (const std::string& text, const size_t position) -> Result {
			return separator_parser->operator()(text, position);
		}
	);
}

Parser end(void) {
	return std::make_shared<ParserFunction>(
		[=] (const std::string& text, const size_t position) -> Result {
			return position == text.size()
				? Result{true, node::Node(), position}
				: Result();
		}
	);
}

Parser operator"" _s(const char symbol) {
	return std::make_shared<ParserFunction>(
		[=] (const std::string& text, const size_t position) -> Result {
			return position < text.size() && text[position] == symbol
				? Result{
					true,
					node::Node{"", std::string(1, symbol), {}},
					position + 1
				}
				: Result();
		}
	);
}

Parser operator"" _t(const char* text, const size_t length) {
	return lexeme(
		separation(
			nothing(),
			std::accumulate(
				text,
				text + length,
				nothing(),
				[] (const Parser& parser, const char symbol) {
					return parser >> operator"" _s(symbol);
				}
			)
		)
	);
}

Parser any(void) {
	return std::make_shared<ParserFunction>(
		[=] (const std::string& text, const size_t position) -> Result {
			return position < text.size()
				? Result{
					true,
					node::Node{"", std::string(1, text[position]), {}},
					position + 1
				}
				: Result();
		}
	);
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
	return any(" \t\n\v\f\r");
}

Parser letter(void) {
	return any("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");
}

Parser digit(void) {
	return any("0123456789");
}

Parser word(void) {
	return letter() | digit() | '_'_s;
}

Parser word(const Parser& parser) {
	return separation(nothing(), boundary() >> parser >> boundary());
}

node::Node parse(const Parser& parser, const std::string& text) {
	const auto result = parser->operator()(text, 0);
	if (!std::get<0>(result)) {
		throw std::runtime_error(
			"parse error on position " + std::to_string(std::get<2>(result))
		);
	}

	return std::get<1>(result);
}

}
}
}
