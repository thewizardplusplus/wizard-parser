#ifndef THEWIZARDPLUSPLUS_WIZARD_PARSER_PARSER_PARSING_RESULT_HEADER
#define THEWIZARDPLUSPLUS_WIZARD_PARSER_PARSER_PARSING_RESULT_HEADER

#include "ast_node.hpp"
#include "../lexer/token.hpp"
#include "../vendor/gsl/span.hpp"
#include <cstddef>
#include <optional>

namespace thewizardplusplus::wizard_parser::parser {

struct parsing_result {
	std::optional<ast_node> node;
	gsl::span<lexer::token> rest_tokens;

	std::size_t get_last_token_offset() const;
};

}
#endif
