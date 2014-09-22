#ifndef NODE_H
#define NODE_H

#include <vector>
#include <string>
#include <ostream>

namespace thewizardplusplus {
namespace wizard_parser {

struct Node;
using NodeGroup = std::vector<Node>;
struct Node {
	std::string name;
	std::string value;
	NodeGroup children;
};

std::ostream& operator<<(std::ostream& stream, const Node& node);
NodeGroup children(const Node& node, const size_t level = -1);

}
}
#endif
