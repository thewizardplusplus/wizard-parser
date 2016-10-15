#include "ast_node_flag.hpp"

namespace parser {

ast_node_flag operator|(
	const ast_node_flag flag_1,
	const ast_node_flag flag_2
) {
	return static_cast<ast_node_flag>(
		static_cast<std::uint8_t>(flag_1) | static_cast<std::uint8_t>(flag_2)
	);
}

bool operator&(
	const ast_node_flag flag_union,
	const ast_node_flag sought_flag
) {
	return static_cast<std::uint8_t>(flag_union)
		& static_cast<std::uint8_t>(sought_flag);
}

}
