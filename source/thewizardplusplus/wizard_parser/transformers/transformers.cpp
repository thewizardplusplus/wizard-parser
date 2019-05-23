#include "transformers.hpp"
#include "../vendor/range/v3/view/filter.hpp"
#include "../vendor/range/v3/to_container.hpp"
#include "../vendor/range/v3/view/transform.hpp"
#include "../vendor/range/v3/view/join.hpp"
#include <vector>

namespace thewizardplusplus::wizard_parser::transformers {

parser::ast_node remove_nothings(const parser::ast_node& ast) {
	const auto type = (+parser::ast_node_type::nothing)._to_string();
	const auto new_children = ast.children
		| ranges::view::filter([&] (const auto& ast) { return ast.type != type; })
		| ranges::to_<parser::ast_node_group>();
	return {ast.type, ast.value, new_children, ast.offset};
}

parser::ast_node join_sequences(const parser::ast_node& ast) {
	const auto type = (+parser::ast_node_type::sequence)._to_string();
	if (ast.type != type) {
		return ast;
	}

	const auto new_children_set = ast.children
		| ranges::view::transform([&] (const auto& ast) {
			return ast.type == type ? ast.children : parser::ast_node_group{ast};
		})
		| ranges::to_<std::vector<parser::ast_node_group>>();
	const auto new_children = new_children_set
		| ranges::view::join
		| ranges::to_<parser::ast_node_group>();
	return {ast.type, ast.value, new_children, ast.offset};
}

}
