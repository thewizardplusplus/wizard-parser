#include "Parser.h"
#include <numeric>

namespace thewizardplusplus {
namespace wizard_parser {

Parser hide(const Parser& parser) {
	return [=] (const std::string& text, const size_t position) -> Result {
		const auto result = parser(text, position);
		return std::get<0>(result)
			? Result{true, Node(), std::get<2>(result)}
			: Result();
	};
}

Parser name(const std::string& name, const Parser& parser) {
	return [=] (const std::string& text, const size_t position) -> Result {
		const auto result = parser(text, position);
		return std::get<0>(result)
			? Result{
				true,
				{name, std::get<1>(result).value, std::get<1>(result).children},
				std::get<2>(result)
			}
			: Result();
	};
}

Parser plain(const Parser& parser, const size_t level) {
	return [=] (const std::string& text, const size_t position) -> Result {
		const auto result = parser(text, position);
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
	};
}

Parser lexeme(const Parser& parser) {
	return [=] (const std::string& text, const size_t position) -> Result {
		const auto result = plain(parser)(text, position);
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
			: Result();
	};
}

Parser operator>>(const Parser& parser1, const Parser& parser2) {
	return [=] (const std::string& text, const size_t position) -> Result {
		auto nodes = NodeGroup();

		const auto result1 = parser1(text, position);
		if (!std::get<0>(result1)) {
			return Result();
		} else if (!is_empty(std::get<1>(result1))) {
			nodes.push_back(std::get<1>(result1));
		}

		const auto result2 = parser2(text, std::get<2>(result1));
		if (!std::get<0>(result2)) {
			return Result();
		} else if (!is_empty(std::get<1>(result2))) {
			nodes.push_back(std::get<1>(result2));
		}

		return Result{true, Node{"", "", nodes}, std::get<2>(result2)};
	};
}

Parser operator|(const Parser& parser1, const Parser& parser2) {
	return [=] (const std::string& text, const size_t position) -> Result {
		const auto result = parser1(text, position);
		return std::get<0>(result) ? result : parser2(text, position);
	};
}

Parser operator!(const Parser& parser) {
	return parser | nothing();
}

Parser operator*(const Parser& parser) {
	return [=] (const std::string& text, const size_t position) -> Result {
		auto nodes = NodeGroup();
		auto end_position = position;
		while (true) {
			const auto result = parser(text, end_position);
			if (!std::get<0>(result)) {
				break;
			}

			if (!is_empty(std::get<1>(result))) {
				nodes.push_back(std::get<1>(result));
			}
			end_position = std::get<2>(result);
		}

		return Result{true, {"", "", nodes}, end_position};
	};
}

Parser operator+(const Parser& parser) {
	return plain(parser >> *parser);
}

Parser operator-(const Parser& parser1, const Parser& parser2) {
	return [=] (const std::string& text, const size_t position) -> Result {
		const auto result = parser1(text, position);
		return std::get<0>(result) && !std::get<0>(parser2(text, position))
			? result
			: Result();
	};
}

Parser operator"" _s(const char symbol) {
	return [=] (const std::string& text, const size_t position) -> Result {
		return position < text.size() && text[position] == symbol
			? Result{
				true,
				Node{"", std::string(1, symbol), {}},
				position + 1
			}
			: Result();
	};
}

Parser operator"" _t(const char* text, const size_t length) {
	return lexeme(
		std::accumulate(
			text,
			text + length,
			nothing(),
			[] (const Parser& parser, const char symbol) {
				return parser >> operator"" _s(symbol);
			}
		)
	);
}

Parser nothing(void) {
	return [=] (const std::string& text, const size_t position) -> Result {
		(void)text;
		return Result{true, Node(), position};
	};
}

Parser end(void) {
	return [=] (const std::string& text, const size_t position) -> Result {
		return position == text.size()
			? Result{true, Node(), position}
			: Result();
	};
}

Parser some(const std::string& symbols) {
	if (symbols.empty()) {
		throw std::invalid_argument("some() at empty string");
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

Parser list(const Parser& parser, const Parser& separator) {
	return plain(parser >> *(hide(separator) >> parser), 3);
}

Node parse(const std::string& text, const Parser& parser) {
	const auto result = parser(text, 0);
	if (!std::get<0>(result)) {
		throw std::runtime_error("parse error");
	}

	return std::get<1>(result);
}

}
}
