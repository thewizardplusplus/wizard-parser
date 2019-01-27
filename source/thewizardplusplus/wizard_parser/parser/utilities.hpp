#ifndef THEWIZARDPLUSPLUS_WIZARD_PARSER_PARSER_UTILITIES_HEADER
#define THEWIZARDPLUSPLUS_WIZARD_PARSER_PARSER_UTILITIES_HEADER

#include "ast_node.hpp"
#include <vector>

namespace thewizardplusplus::wizard_parser::parser {

void append_node(ast_node_group& nodes, ast_node&& node);

}
#endif
