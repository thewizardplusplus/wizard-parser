#include "type_assignable_parser.hpp"
#include "ast_node.hpp"

namespace thewizardplusplus::wizard_parser::parser {

type_assignable_parser::type_assignable_parser(std::string type): type{type} {}

parsing_result type_assignable_parser::process_parsed_result(
	parsing_result result
) const {
	if (result.node->flags & ast_node_flag::named) {
		return result;
	}

	result.node->type = type;
	result.node->flags = result.node->flags | ast_node_flag::named;

	return result;
}

}
