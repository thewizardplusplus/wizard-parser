#ifndef THEWIZARDPLUSPLUS_WIZARD_PARSER_PARSER_PARSING_RESULT_HEADER
#define THEWIZARDPLUSPLUS_WIZARD_PARSER_PARSER_PARSING_RESULT_HEADER

#include "ast_node.hpp"
#include "../lexer/token.hpp"
#include <optional>

namespace thewizardplusplus::wizard_parser::parser {

struct parsing_result {
	std::optional<ast_node> node;
	lexer::token_span rest_tokens;
};

}
#endif
