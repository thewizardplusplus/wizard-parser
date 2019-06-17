#include "transform.hpp"
#include "../vendor/range/v3/view/transform.hpp"
#include "../vendor/range/v3/numeric/accumulate.hpp"

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

parser::ast_node transform(
	const parser::ast_node& ast,
	const ast_node_handler_group& handlers
) {
	// use the lambda to call the correct overload
	const auto transformer = [] (const auto& ast, const auto& handler) {
		return transform(ast, handler);
	};
	return ranges::accumulate(handlers, ast, transformer);
}

}
