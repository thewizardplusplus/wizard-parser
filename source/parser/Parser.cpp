#include "Parser.h"
#include <numeric>

namespace parser {

const Parser nothing = [=] (const std::string& text, const size_t& position) {
	(void)text;
	return Result{true, Node(), position};
};

const Parser end = [=] (const std::string& text, const size_t& position) {
	return position == text.size()
		? Result{true, Node(), position}
		: Result();
};

Parser operator"" _s(char symbol) {
	return [=] (const std::string& text, const size_t& position) {
		return text.size() > position && text[position] == symbol
			? Result{
				true,
				Node{"symbol", std::string(1, symbol), {}},
				position + 1
			}
			: Result();
	};
}

Parser operator"" _t(const char* text, size_t length) {
	return name(
		"text",
		lexeme(
			std::accumulate(
				text,
				text + length,
				nothing,
				[] (const Parser& parser, const char& symbol) {
					return parser >> operator"" _s(symbol);
				}
			)
		)
	);
}

Parser operator>>(const Parser& parser1, const Parser& parser2) {
	return [=] (const std::string& text, const size_t& position) -> Result {
		auto nodes = NodeGroup();

		const auto result1 = parser1(text, position);
		if (!std::get<0>(result1)) {
			return Result();
		} else if (
			!std::get<1>(result1).value.empty()
			|| !std::get<1>(result1).children.empty()
		) {
			nodes.push_back(std::get<1>(result1));
		}

		const auto result2 = parser2(text, std::get<2>(result1));
		if (!std::get<0>(result2)) {
			return Result();
		} else if (
			!std::get<1>(result2).value.empty()
			|| !std::get<1>(result2).children.empty()
		) {
			nodes.push_back(std::get<1>(result2));
		}

		return Result{true, Node{"", "", nodes}, std::get<2>(result2)};
	};
}

Parser operator|(const Parser& parser1, const Parser& parser2) {
	return [=] (const std::string& text, const size_t& position) -> Result {
		const auto result = parser1(text, position);
		return std::get<0>(result) ? result : parser2(text, position);
	};
}

Parser operator!(const Parser& parser) {
	return parser | nothing;
}

Parser operator*(const Parser& parser) {
	return [=] (const std::string& text, const size_t& position) -> Result {
		auto nodes = NodeGroup();
		auto end_position = position;
		while (true) {
			const auto result = parser(text, end_position);
			if (!std::get<0>(result)) {
				break;
			}

			if (
				!std::get<1>(result).value.empty()
				|| !std::get<1>(result).children.empty()
			) {
				nodes.push_back(std::get<1>(result));
			}
			end_position = std::get<2>(result);
		}

		return Result{true, {"", "", nodes}, end_position};
	};
}

Parser operator-(const Parser& parser1, const Parser& parser2) {
	return [=] (const std::string& text, const size_t& position) -> Result {
		const auto result = parser1(text, position);
		return std::get<0>(result) && !std::get<0>(parser2(text, position))
			? result
			: Result();
	};
}

Parser hide(const Parser& parser) {
	return [=] (const std::string& text, const size_t& position) -> Result {
		const auto result = parser(text, position);
		return std::get<0>(result)
			? Result{true, Node(), std::get<2>(result)}
			: Result();
	};
}

Parser plain(const Parser& parser) {
	return [=] (const std::string& text, const size_t& position) -> Result {
		const auto result = parser(text, position);
		return std::get<0>(result)
			? Result{
				true,
				{
					std::get<1>(result).name,
					std::get<1>(result).value,
					children(std::get<1>(result))
				},
				std::get<2>(result)
			}
			: Result();
	};
}

Parser lexeme(const Parser& parser) {
	return [=] (const std::string& text, const size_t& position) -> Result {
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

Parser name(const std::string& name, const Parser& parser) {
	return [=] (const std::string& text, const size_t& position) -> Result {
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

}
