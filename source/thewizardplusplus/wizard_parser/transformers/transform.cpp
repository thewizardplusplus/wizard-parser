#include "transform.hpp"
#include "../vendor/range/v3/view/transform.hpp"

namespace thewizardplusplus::wizard_parser::transformers {

parser::ast_node transform(
	const parser::ast_node& ast,
	const ast_node_handler& handler
) {
	const auto new_children = ast.children
		| ranges::view::transform([&] (const auto& ast) {
			return transform(ast, handler);
		});
	return handler({ast.type, ast.value, new_children, ast.offset});
}

}
