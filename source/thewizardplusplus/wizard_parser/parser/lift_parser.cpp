#include "lift_parser.hpp"
#include "ast_node.hpp"

namespace thewizardplusplus::wizard_parser::parser {

parsing_result lift_parser::process_parsed_result(parsing_result result) const {
	if (
		result.node->flags & ast_node_flag::important
		|| result.node->children.size() != 1
	) {
		return result;
	}

	return {result.node->children.front(), result.rest_tokens};
}

}
