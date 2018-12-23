#ifndef THEWIZARDPLUSPLUS_WIZARD_PARSER_PARSER_AST_NODE_FLAG_HEADER
#define THEWIZARDPLUSPLUS_WIZARD_PARSER_PARSER_AST_NODE_FLAG_HEADER

#include <cstdint>

namespace thewizardplusplus::wizard_parser::parser {

enum class ast_node_flag: std::uint8_t {
	none,
	named,
	important
};

ast_node_flag operator|(const ast_node_flag flag_1, const ast_node_flag flag_2);
bool operator&(const ast_node_flag flag_union, const ast_node_flag sought_flag);

}
#endif
