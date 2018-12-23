#include "lift_parser.hpp"
#include "ast_node_flag.hpp"
#include <utility>

namespace thewizardplusplus::wizard_parser::parser {

parsing_result lift_parser::process_parsed_result(parsing_result result) const {
	if (
		result.node->flags & ast_node_flag::important
		|| result.node->children.size() != 1
	) {
		return result;
	}

	return {
		std::move(result.node->children.front()),
		std::move(result.rest_tokens)
	};
}

}
