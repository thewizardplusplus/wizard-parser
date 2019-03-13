#include "ast_node.hpp"
#include <tuple>

namespace thewizardplusplus::wizard_parser::parser {

std::tuple<std::string, std::string, ast_node_group, optional_offset> to_tuple(
	const ast_node& ast
) {
	return std::make_tuple(ast.type, ast.value, ast.children, ast.offset);
}

bool operator==(const ast_node& ast_1, const ast_node& ast_2) {
	return to_tuple(ast_1) == to_tuple(ast_2);
}

}
