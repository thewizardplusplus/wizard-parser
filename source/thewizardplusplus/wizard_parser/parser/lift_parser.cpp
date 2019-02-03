#include "lift_parser.hpp"
#include "ast_node.hpp"

namespace thewizardplusplus::wizard_parser::parser {

parsing_result lift_parser::process_parsed_result(
	const parsing_result& result
) const {
	return result.node->children.size() == 1
		? parsing_result{result.node->children.front(), result.rest_tokens}
		: result;
}

}
