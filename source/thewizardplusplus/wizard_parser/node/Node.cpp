#include "Node.h"
#include <numeric>
#include <algorithm>

namespace thewizardplusplus {
namespace wizard_parser {
namespace node {

const std::string XML_CDATA_START = "<![CDATA[";
const std::string XML_CDATA_END = "]]>";
const size_t XML_CDATA_ESCAPING_INSERT_SHIFT = 1;

static std::string escape(const std::string& text) {
	if (text.empty()) {
		return "";
	}

	auto text_copy = text;
	size_t last_index = 0;
	while (true) {
		last_index = text_copy.find(XML_CDATA_END, last_index);
		if (last_index == std::string::npos) {
			break;
		}

		text_copy.insert(
			last_index + XML_CDATA_ESCAPING_INSERT_SHIFT,
			XML_CDATA_END + XML_CDATA_START
		);
		last_index +=
			XML_CDATA_ESCAPING_INSERT_SHIFT
			+ XML_CDATA_START.size()
			+ XML_CDATA_END.size();
	}

	return XML_CDATA_START + text_copy + XML_CDATA_END;
}

std::ostream& operator<<(std::ostream& stream, const Node& node) {
	stream << "<node>";
	stream << "<name>" << escape(node.name) << "</name>";
	stream << "<value>" << escape(node.value) << "</value>";

	stream << "<children>";
	for (const auto& child: node.children) {
		stream << child;
	}
	stream << "</children>";

	stream << "</node>";
	return stream;
}

bool is_empty(const Node& node) {
	return node.value.empty() && node.children.empty();
}

NodeGroup leaves(const Node& node) {
	return !node.children.empty()
		? std::accumulate(
			node.children.begin(),
			node.children.end(),
			NodeGroup(),
			[] (
				const NodeGroup& all_children,
				const Node& node
			) -> NodeGroup {
				auto all_children_copy = all_children;

				const auto node_children = leaves(node);
				std::copy(
					node_children.begin(),
					node_children.end(),
					std::back_inserter(all_children_copy)
				);

				return all_children_copy;
			}
		)
		: NodeGroup{node};
}

}
}
}
