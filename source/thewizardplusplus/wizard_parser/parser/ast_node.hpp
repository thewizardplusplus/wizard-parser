#ifndef THEWIZARDPLUSPLUS_WIZARD_PARSER_PARSER_AST_NODE_HEADER
#define THEWIZARDPLUSPLUS_WIZARD_PARSER_PARSER_AST_NODE_HEADER

#include "../vendor/enum-flags/flags.hpp"
#include <cstdint>
#include <string>
#include <vector>

namespace thewizardplusplus::wizard_parser::parser {

enum class ast_node_flag: std::uint8_t {
	none = 1 << 0,
	named = 1 << 1,
	important = 1 << 2
};

}

ALLOW_FLAGS_FOR_ENUM(thewizardplusplus::wizard_parser::parser::ast_node_flag)

namespace thewizardplusplus::wizard_parser::parser {

struct ast_node {
	std::string type;
	std::string value;
	std::vector<ast_node> children;
	flags::flags<ast_node_flag> flags = ast_node_flag::none;
};

using ast_node_group = std::vector<ast_node>;

}
#endif
