#include "common.hpp"
#include <string>
#include <unordered_set>
#include <iterator>
#include <algorithm>

const auto ignorable_nodes = std::unordered_set<std::string>{"nothing", "eoi"};

namespace thewizardplusplus::wizard_parser::parser {

void append_node(ast_node_group& nodes, const ast_node& node) {
	const auto appended_nodes =
		node.type == "sequence" ? node.children : ast_node_group{node};
	std::copy_if(
		std::cbegin(appended_nodes),
		std::cend(appended_nodes),
		std::back_inserter(nodes),
		[&] (const auto& node) { return ignorable_nodes.count(node.type) == 0; }
	);
}

}
