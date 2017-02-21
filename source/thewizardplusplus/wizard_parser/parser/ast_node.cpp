#include "ast_node.hpp"
#include "../utilities/string_utilities.hpp"
#include <iterator>

using namespace std::string_literals;
using namespace thewizardplusplus::wizard_parser::utilities;

namespace thewizardplusplus {
namespace wizard_parser {
namespace parser {

std::ostream& operator<<(std::ostream& out, const ast_node& ast) {
	out << to_string(ast);
	return out;
}

std::string to_string(const ast_node& ast) {
	auto result = "{"s + R"("type":)" + quote(ast.type);

	if (!ast.value.empty()) {
		result += ","s + R"("value":)" + quote(ast.value);
	}

	if (!ast.children.empty()) {
		result += ","s + R"("children":)" + '[';

		for (
			auto child = std::cbegin(ast.children);
			child != std::cend(ast.children);
			++child
		) {
			if (child != std::cbegin(ast.children)) {
				result += ',';
			}
			result += to_string(*child);
		}

		result += ']';
	}

	result += '}';
	return result;
}

}
}
}
