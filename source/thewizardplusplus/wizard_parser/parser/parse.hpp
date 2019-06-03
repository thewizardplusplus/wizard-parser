#ifndef THEWIZARDPLUSPLUS_WIZARD_PARSER_PARSER_PARSE_HEADER
#define THEWIZARDPLUSPLUS_WIZARD_PARSER_PARSER_PARSE_HEADER

#include "rule_parser.hpp"
#include "../lexer/token.hpp"
#include "../transformers/transform.hpp"
#include "../transformers/transformers.hpp"

namespace thewizardplusplus::wizard_parser::parser {

parsing_result parse(
	const rule_parser::pointer& parser,
	const lexer::token_span& tokens,
	const transformers::ast_node_handler_group& handlers = {
		transformers::remove_nothings,
		transformers::join_sequences
	}
);
ast_node parse_all(
	const rule_parser::pointer& parser,
	const lexer::token_span& tokens,
	const transformers::ast_node_handler_group& handlers = {
		transformers::remove_nothings,
		transformers::join_sequences
	}
);

}
#endif
