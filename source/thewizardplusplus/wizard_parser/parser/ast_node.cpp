#include "ast_node.hpp"
#include "../utilities/string_utilities.hpp"
#include <iterator>

using namespace utilities;

namespace parser {

std::ostream& operator<<(std::ostream& out, const ast_node& ast) {
	out << '{' << R"("type":)" << quote(ast.type);

	if (!ast.value.empty()) {
		out << ',' << R"("value":)" << quote(ast.value);
	}

	if (!ast.children.empty()) {
		out << ',' << R"("children":)" << '[';

		for (
			auto child = std::cbegin(ast.children);
			child != std::cend(ast.children);
			++child
		) {
			if (child != std::cbegin(ast.children)) {
				out << ',';
			}
			out << *child;
		}

		out << ']';
	}

	out << '}';
	return out;
}

}
