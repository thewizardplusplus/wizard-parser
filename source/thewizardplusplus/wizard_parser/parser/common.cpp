#include "common.hpp"
#include <string>
#include <unordered_set>
#include <iterator>
#include <algorithm>

namespace thewizardplusplus::wizard_parser::parser {

const auto ignorable_nodes = std::unordered_set<std::string>{
	(+ast_node_type::nothing)._to_string(),
	(+ast_node_type::eoi)._to_string()
};

void append_node(ast_node_group& nodes, const ast_node& node) {
	const auto appended_nodes =
		node.type != (+ast_node_type::sequence)._to_string()
			? ast_node_group{node}
			: node.children;
	std::copy_if(
		std::cbegin(appended_nodes),
		std::cend(appended_nodes),
		std::back_inserter(nodes),
		[&] (const auto& node) { return ignorable_nodes.count(node.type) == 0; }
	);
}

}
