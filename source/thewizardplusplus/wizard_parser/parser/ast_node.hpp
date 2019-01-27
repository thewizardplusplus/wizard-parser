#ifndef THEWIZARDPLUSPLUS_WIZARD_PARSER_PARSER_AST_NODE_HEADER
#define THEWIZARDPLUSPLUS_WIZARD_PARSER_PARSER_AST_NODE_HEADER

#include <cstdint>
#include <string>
#include <vector>

namespace thewizardplusplus::wizard_parser::parser {

enum class ast_node_flag: std::uint8_t {
	none = 1 << 0,
	named = 1 << 1,
	important = 1 << 2
};

struct ast_node {
	std::string type;
	std::string value;
	std::vector<ast_node> children;
	ast_node_flag flags = ast_node_flag::none;
};

using ast_node_group = std::vector<ast_node>;

ast_node_flag operator|(
	const ast_node_flag& flag_1,
	const ast_node_flag& flag_2
);
bool operator&(const ast_node_flag& flag_union, const ast_node_flag& some_flag);

}
#endif
