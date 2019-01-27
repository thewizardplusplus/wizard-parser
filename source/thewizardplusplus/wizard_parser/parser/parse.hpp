#ifndef THEWIZARDPLUSPLUS_WIZARD_PARSER_PARSER_PARSE_HEADER
#define THEWIZARDPLUSPLUS_WIZARD_PARSER_PARSER_PARSE_HEADER

#include "rule_parser.hpp"
#include "../lexer/token.hpp"
#include "ast_node.hpp"
#include "../lexer/lexeme.hpp"
#include <string>

namespace thewizardplusplus::wizard_parser::parser {

ast_node parse(
	const rule_parser::pointer& rule,
	const lexer::token_span& tokens
);
ast_node parse(
	const lexer::lexeme_group& lexemes,
	const rule_parser::pointer& rule,
	std::string code
);

}
#endif
