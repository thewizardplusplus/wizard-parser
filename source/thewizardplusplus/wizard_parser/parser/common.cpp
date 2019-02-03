#include "common.hpp"
#include <iterator>
#include <algorithm>

namespace thewizardplusplus::wizard_parser::parser {

void append_node(ast_node_group& nodes, const ast_node& node) {
	const auto appended_nodes =
		node.type != (+ast_node_type::sequence)._to_string()
			? ast_node_group{node}
			: node.children;
	std::copy(
		std::cbegin(appended_nodes),
		std::cend(appended_nodes),
		std::back_inserter(nodes)
	);
}

}
