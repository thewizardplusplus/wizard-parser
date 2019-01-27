#include "type_assignable_parser.hpp"
#include "ast_node.hpp"

namespace thewizardplusplus::wizard_parser::parser {

type_assignable_parser::type_assignable_parser(const std::string& type):
	type{type}
{}

parsing_result type_assignable_parser::process_parsed_result(
	const parsing_result& result
) const {
	if (result.node->flags & ast_node_flag::named) {
		return result;
	}

	auto result_copy = result;
	result_copy.node->type = type;
	result_copy.node->flags = result.node->flags | ast_node_flag::named;

	return result_copy;
}

}
