#include "utilities.hpp"
#include "../utilities/set_utilities.hpp"
#include <string>
#include <unordered_set>
#include <utility>

using namespace utilities;

const auto ignorable_nodes = std::unordered_set<std::string>{"nothing", "eoi"};

namespace parser {

void append_node(std::list<ast_node>& nodes, ast_node&& node) {
	if (node.type == "sequence") {
		for (auto&& child_node: node.children) {
			if (contains(ignorable_nodes, child_node.type)) {
				continue;
			}

			nodes.push_back(std::move(child_node));
		}
	} else if (!contains(ignorable_nodes, node.type)) {
		nodes.push_back(std::move(node));
	}
}

}
