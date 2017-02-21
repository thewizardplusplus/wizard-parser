#include "ast_node.hpp"
#include <iterator>
#include <algorithm>

using namespace nlohmann;

namespace thewizardplusplus {
namespace wizard_parser {
namespace parser {

std::ostream& operator<<(std::ostream& out, const ast_node& ast) {
	out << to_string(ast);
	return out;
}

std::string to_string(const ast_node& ast) {
	return to_json(ast).dump();
}

json to_json(const ast_node& ast) {
	auto result = json{{"type", ast.type}};
	if (!ast.value.empty()) {
		result["value"] = ast.value;
	}
	if (!ast.children.empty()) {
		result["children"] = json{};
		std::for_each(
			std::cbegin(ast.children),
			std::cend(ast.children),
			[&result] (const auto& child) {
				result["children"].push_back(to_json(child));
			}
		);
	}

	return result;
}

}
}
}
