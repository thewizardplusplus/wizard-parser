#include "transformers.hpp"
#include "../vendor/range/v3/view/filter.hpp"
#include "../vendor/range/v3/to_container.hpp"

namespace thewizardplusplus::wizard_parser::transformers {

parser::ast_node remove_nothings(const parser::ast_node& ast) {
	const auto type = (+parser::ast_node_type::nothing)._to_string();
	const auto new_children = ast.children
		| ranges::view::filter([&] (const auto& ast) { return ast.type != type; })
		| ranges::to_<parser::ast_node_group>();
	return {ast.type, ast.value, new_children, ast.offset};
}

}
