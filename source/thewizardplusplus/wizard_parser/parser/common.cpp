#include "common.hpp"
#include <string>
#include <unordered_set>

const auto ignorable_nodes = std::unordered_set<std::string>{"nothing", "eoi"};

namespace thewizardplusplus::wizard_parser::parser {

void append_node(ast_node_group& nodes, const ast_node& node) {
	if (node.type == "sequence") {
		for (const auto& child_node: node.children) {
			if (ignorable_nodes.count(child_node.type) == 0) {
				nodes.push_back(child_node);
			}
		}
	} else if (ignorable_nodes.count(node.type) == 0) {
		nodes.push_back(node);
	}
}

}
