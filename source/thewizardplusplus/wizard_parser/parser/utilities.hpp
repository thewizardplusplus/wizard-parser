#ifndef THEWIZARDPLUSPLUS_WIZARD_PARSER_PARSER_UTILITIES_HEADER
#define THEWIZARDPLUSPLUS_WIZARD_PARSER_PARSER_UTILITIES_HEADER

#include "ast_node.hpp"
#include <vector>

namespace thewizardplusplus::wizard_parser::parser {

void append_node(std::vector<ast_node>& nodes, ast_node&& node);

}
#endif
