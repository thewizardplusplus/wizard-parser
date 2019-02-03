#ifndef THEWIZARDPLUSPLUS_WIZARD_PARSER_LEXER_TOKEN_HEADER
#define THEWIZARDPLUSPLUS_WIZARD_PARSER_LEXER_TOKEN_HEADER

#include "../vendor/gsl/span.hpp"
#include <string>
#include <cstddef>
#include <vector>

namespace thewizardplusplus::wizard_parser::lexer {

struct token {
	std::string type;
	std::string value;
	std::size_t offset;
};

using token_group = std::vector<token>;

using token_span = gsl::span<token>;

std::size_t get_offset(const token_span& tokens);

}
#endif
