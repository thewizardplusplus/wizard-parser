#ifndef THEWIZARDPLUSPLUS_WIZARD_PARSER_PARSER_PARSE_HEADER
#define THEWIZARDPLUSPLUS_WIZARD_PARSER_PARSER_PARSE_HEADER

#include "rule_parser.hpp"
#include "../lexer/token_group.hpp"
#include "ast_node.hpp"

namespace thewizardplusplus {
namespace wizard_parser {
namespace parser {

ast_node parse(
	const rule_parser::pointer& rule,
	const lexer::token_group& tokens
);

}
}
}
#endif
