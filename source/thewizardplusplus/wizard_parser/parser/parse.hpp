#ifndef THEWIZARDPLUSPLUS_WIZARD_PARSER_PARSER_PARSE_HEADER
#define THEWIZARDPLUSPLUS_WIZARD_PARSER_PARSER_PARSE_HEADER

#include "rule_parser.hpp"
#include "../lexer/token.hpp"
#include "../transformers/transform.hpp"

namespace thewizardplusplus::wizard_parser::parser {

parsing_result parse(
	const rule_parser::pointer& parser,
	const lexer::token_span& tokens,
	const transformers::ast_node_handler_group& handlers
		= transformers::default_ast_node_handlers
);
ast_node parse_all(
	const rule_parser::pointer& parser,
	const lexer::token_span& tokens,
	const transformers::ast_node_handler_group& handlers
		= transformers::default_ast_node_handlers
);

}
#endif
