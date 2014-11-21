#ifndef WIZARD_PARSER_NODE_NODE_HEADER
#define WIZARD_PARSER_NODE_NODE_HEADER

#include <vector>
#include <string>
#include <ostream>

namespace thewizardplusplus {
namespace wizard_parser {
namespace node {

struct Node;
using NodeGroup = std::vector<Node>;
struct Node {
	std::string name;
	std::string value;
	NodeGroup children;
};

std::ostream& operator<<(std::ostream& stream, const Node& node);
bool is_empty(const Node& node);
NodeGroup leaves(const Node& node);

}
}
}
#endif
