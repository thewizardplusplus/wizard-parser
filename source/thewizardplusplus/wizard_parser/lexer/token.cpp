#include "token.hpp"
#include "../utilities/utilities.hpp"
#include <tuple>

namespace thewizardplusplus::wizard_parser::lexer {

std::tuple<std::string, std::string, std::size_t> to_tuple(
	const token& some_token
) {
	return std::make_tuple(some_token.type, some_token.value, some_token.offset);
}

bool operator==(const token& token_1, const token& token_2) {
	return to_tuple(token_1) == to_tuple(token_2);
}

std::size_t get_offset(const token_span& tokens) {
	return !tokens.empty() ? tokens[0].offset : utilities::integral_infinity;
}

}
