#ifndef NODE_H
#define NODE_H

#include <vector>
#include <string>
#include <ostream>

namespace parser {

struct Node;
using NodeGroup = std::vector<Node>;
struct Node {
	std::string name;
	std::string value;
	NodeGroup children;
};

std::ostream& operator<<(std::ostream& stream, const Node& node);
NodeGroup children(const Node& node);

}
#endif
