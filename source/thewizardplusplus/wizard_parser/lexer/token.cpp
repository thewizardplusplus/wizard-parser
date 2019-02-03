#include "token.hpp"
#include "../utilities/utilities.hpp"

namespace thewizardplusplus::wizard_parser::lexer {

std::size_t get_offset(const token_span& tokens) {
	return !tokens.empty() ? tokens[0].offset : utilities::integral_infinity;
}

}
