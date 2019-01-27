#include "ast_node.hpp"

namespace thewizardplusplus::wizard_parser::parser {

using underlying_flag_t = std::underlying_type_t<ast_node_flag>;

ast_node_flag operator|(
	const ast_node_flag& flag_1,
	const ast_node_flag& flag_2
) {
	return static_cast<ast_node_flag>(
		static_cast<underlying_flag_t>(flag_1)
			| static_cast<underlying_flag_t>(flag_2)
	);
}

bool operator&(
	const ast_node_flag& flag_union,
	const ast_node_flag& some_flag
) {
	return static_cast<underlying_flag_t>(flag_union)
		& static_cast<underlying_flag_t>(some_flag);
}

}
