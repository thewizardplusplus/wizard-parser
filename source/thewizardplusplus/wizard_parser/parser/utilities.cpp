#include "utilities.hpp"
#include <string>
#include <unordered_set>
#include <utility>

const auto ignorable_nodes = std::unordered_set<std::string>{"nothing", "eoi"};

namespace thewizardplusplus {
namespace wizard_parser {
namespace parser {

void append_node(std::vector<ast_node>& nodes, ast_node&& node) {
	if (node.type == "sequence") {
		for (auto&& child_node: node.children) {
			if (ignorable_nodes.count(child_node.type) == 0) {
				nodes.push_back(std::move(child_node));
			}
		}
	} else if (ignorable_nodes.count(node.type) == 0) {
		nodes.push_back(std::move(node));
	}
}

}
}
}
