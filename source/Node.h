#ifndef NODE_H
#define NODE_H

#include <string>
#include <vector>
#include <ostream>

struct Node {
	std::string value;
	std::vector<Node> children;
};

std::ostream& operator<<(std::ostream& stream, const Node& node);
#endif
