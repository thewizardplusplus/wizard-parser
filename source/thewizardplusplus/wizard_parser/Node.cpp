#include "Node.h"
#include <numeric>
#include <algorithm>

namespace thewizardplusplus {
namespace wizard_parser {

static std::string escape(const std::string& text) {
	auto escaped_text = std::string();
	for (const auto& symbol: text) {
		if (symbol == '"' || symbol == '\\' || symbol == '/') {
			escaped_text += R"(\)";
		}
		escaped_text += symbol;
	}

	return escaped_text;
}

std::ostream& operator<<(std::ostream& stream, const Node& node) {
	stream << "{";

	if (!node.name.empty()) {
		stream << R"("name":")" << escape(node.name) << R"(")";
	}

	if (!node.value.empty()) {
		if (!node.name.empty()) {
			stream << ",";
		}
		stream << R"("value":")" << escape(node.value) << R"(")";
	}

	if (!node.children.empty()) {
		if (!node.name.empty() || !node.value.empty()) {
			stream << ",";
		}

		stream << R"("children":[)";
		for (size_t i = 0; i < node.children.size(); ++i) {
			if (i > 0) {
				stream << ",";
			}
			stream << node.children[i];
		}
		stream << "]";
	}

	stream << "}";
	return stream;
}

NodeGroup children(const Node& node) {
	return !node.children.empty()
		? std::accumulate(
			node.children.begin(),
			node.children.end(),
			NodeGroup(),
			[] (
				const NodeGroup& all_children,
				const Node& node
			) -> NodeGroup {
				auto supplemented_all_children = all_children;

				const auto node_children = children(node);
				std::copy_if(
					node_children.begin(),
					node_children.end(),
					std::back_inserter(supplemented_all_children),
					[] (const Node& node) {
						return !node.value.empty();
					}
				);

				return supplemented_all_children;
			}
		)
		: NodeGroup{node};
}

}
}
