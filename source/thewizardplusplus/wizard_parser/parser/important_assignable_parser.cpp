#include "important_assignable_parser.hpp"
#include "ast_node.hpp"

namespace thewizardplusplus::wizard_parser::parser {

parsing_result important_assignable_parser::process_parsed_result(
	parsing_result result
) const {
	result.node->flags = result.node->flags | ast_node_flag::important;
	return result;
}

}
