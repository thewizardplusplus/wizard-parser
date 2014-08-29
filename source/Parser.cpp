#include "Parser.h"
#include <numeric>

Parser operator"" _s(char symbol) {
	return [=] (const std::string& text, const size_t& position) {
		return text.size() > position && text[position] == symbol
			? Result{
				true,
				Node{"symbol", std::string(1, symbol), {}},
				position + 1
			}
			: INVALID;
	};
}

Parser operator"" _t(const char* text, size_t length) {
	return name(
		"text",
		std::accumulate(
			text + 1,
			text + length,
			operator"" _s(text[0]),
			[] (const Parser& parser, const char& symbol) {
				return (parser, operator"" _s(symbol));
			}
		)
	);
}

Parser operator,(const Parser& parser1, const Parser& parser2) {
	return [=] (const std::string& text, const size_t& position) -> Result {
		const auto result1 = parser1(text, position);
		if (!std::get<0>(result1)) {
			return INVALID;
		}

		const auto result2 = parser2(text, std::get<2>(result1));
		if (!std::get<0>(result2)) {
			return INVALID;
		}

		return Result{
			true,
			Node{"", "", {std::get<1>(result1), std::get<1>(result2)}},
			std::get<2>(result2)
		};
	};
}

Parser operator|(const Parser& parser1, const Parser& parser2) {
	return [=] (const std::string& text, const size_t& position) -> Result {
		const auto result = parser1(text, position);
		return std::get<0>(result) ? result : parser2(text, position);
	};
}

Parser operator!(const Parser& parser) {
	return [=] (const std::string& text, const size_t& position) -> Result {
		const auto result = parser(text, position);
		return std::get<0>(result) ? result : Result{true, Node(), position};
	};
}

Parser operator*(const Parser& parser) {
	return [=] (const std::string& text, const size_t& position) -> Result {
		auto nodes = std::vector<Node>();
		auto end_position = position;
		while (true) {
			const auto result = parser(text, end_position);
			if (!std::get<0>(result)) {
				break;
			}

			nodes.push_back(std::get<1>(result));
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
			: INVALID;
	};
}

Parser name(const std::string& name, const Parser& parser) {
	return [=] (const std::string& text, const size_t& position) -> Result {
		const auto result = parser(text, position);
		return Result{
			true,
			{name, "", std::get<1>(result).children},
			std::get<2>(result)
		};
	};
}
