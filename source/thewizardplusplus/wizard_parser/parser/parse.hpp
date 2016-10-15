#ifndef THEWIZARDPLUSPLUS_WIZARD_PARSER_PARSER_PARSE_HEADER
#define THEWIZARDPLUSPLUS_WIZARD_PARSER_PARSER_PARSE_HEADER

#include "../lexer/token_group.hpp"
#include "ast_node.hpp"

namespace thewizardplusplus {
namespace wizard_parser {
namespace parser {

ast_node parse(lexer::token_group&& tokens);

}
}
}
#endif
