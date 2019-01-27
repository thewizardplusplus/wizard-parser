#ifndef THEWIZARDPLUSPLUS_WIZARD_PARSER_PARSER_AST_NODE_HEADER
#define THEWIZARDPLUSPLUS_WIZARD_PARSER_PARSER_AST_NODE_HEADER

#include "ast_node_flag.hpp"
#include <string>
#include <vector>

namespace thewizardplusplus::wizard_parser::parser {

struct ast_node {
	std::string type;
	std::string value;
	std::vector<ast_node> children;
	ast_node_flag flags = ast_node_flag::none;
};

}
#endif
