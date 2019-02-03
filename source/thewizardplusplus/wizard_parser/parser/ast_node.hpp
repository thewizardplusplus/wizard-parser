#ifndef THEWIZARDPLUSPLUS_WIZARD_PARSER_PARSER_AST_NODE_HEADER
#define THEWIZARDPLUSPLUS_WIZARD_PARSER_PARSER_AST_NODE_HEADER

#include "../vendor/better-enums/enum_strict.hpp"
#include "../vendor/enum-flags/flags.hpp"
#include <cstdint>
#include <string>
#include <vector>

namespace thewizardplusplus::wizard_parser::parser {

BETTER_ENUM(ast_node_type, std::uint8_t, sequence, nothing, eoi)

enum class ast_node_flag: std::uint8_t {
	none = 1 << 0,
	named = 1 << 1
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
