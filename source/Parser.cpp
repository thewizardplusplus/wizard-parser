#include "Parser.h"

Parser operator,(const Parser& parser1, const Parser& parser2) {
	return [=] (const std::string& text, const size_t& position) -> Result {
		const auto result1 = parser1(text, position);
		if (!result1.valid) {
			return INVALID;
		}

		const auto result2 = parser2(text, result1.position);
		if (!result2.valid) {
			return INVALID;
		}

		return Result{true, "", {result1, result2}, result2.position};
	};
}

Parser operator|(const Parser& parser1, const Parser& parser2) {
	return [=] (const std::string& text, const size_t& position) -> Result {
		const auto result = parser1(text, position);
		return result.valid ? result : parser2(text, position);
	};
}

Parser operator!(const Parser& parser) {
	return [=] (const std::string& text, const size_t& position) -> Result {
		const auto result = parser(text, position);
		return result.valid ? result : Result{true, "", {}, position};
	};
}

Parser operator-(const Parser& parser1, const Parser& parser2) {
	return [=] (const std::string& text, const size_t& position) -> Result {
		const auto result = parser1(text, position);
		return result.valid && !parser2(text, position).valid
			? result
			: INVALID;
	};
}
