#ifndef THEWIZARDPLUSPLUS_WIZARD_PARSER_PARSER_AST_NODE_HEADER
#define THEWIZARDPLUSPLUS_WIZARD_PARSER_PARSER_AST_NODE_HEADER

#include "../vendor/better-enums/enum_strict.hpp"
#include <cstdint>
#include <string>
#include <vector>

namespace thewizardplusplus::wizard_parser::parser {

BETTER_ENUM(ast_node_type, std::uint8_t, sequence, nothing, eoi)

struct ast_node {
	std::string type;
	std::string value;
	std::vector<ast_node> children;
};

using ast_node_group = std::vector<ast_node>;

}
#endif
