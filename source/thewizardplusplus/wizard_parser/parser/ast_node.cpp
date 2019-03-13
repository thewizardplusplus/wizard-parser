#include "ast_node.hpp"

namespace thewizardplusplus::wizard_parser::parser {

bool operator==(const ast_node& ast_1, const ast_node& ast_2) {
	return to_tuple(ast_1) == to_tuple(ast_2);
}

std::ostream& operator<<(std::ostream& stream, const ast_node& ast) {
	stream << nlohmann::json(ast);
	return stream;
}

ast_node_tuple to_tuple(const ast_node& ast) {
	return std::make_tuple(ast.type, ast.value, ast.children, ast.offset);
}

void to_json(nlohmann::json& json, const ast_node& ast) {
	json = {{"type", ast.type}};
	if (!ast.value.empty()) {
		json["value"] = ast.value;
	}
	if (!ast.children.empty()) {
		json["children"] = ast.children;
	}
	if (ast.offset) {
		json["offset"] = *ast.offset;
	}
}

}
