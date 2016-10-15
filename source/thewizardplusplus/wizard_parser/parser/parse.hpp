#ifndef PARSER_PARSE_HEADER
#define PARSER_PARSE_HEADER

#include "../lexer/token_group.hpp"
#include "ast_node.hpp"

namespace parser {

ast_node parse(lexer::token_group&& tokens);

}
#endif
