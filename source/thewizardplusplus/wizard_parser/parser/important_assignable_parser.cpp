#include "important_assignable_parser.hpp"
#include "ast_node_flag.hpp"

namespace thewizardplusplus {
namespace wizard_parser {
namespace parser {

parsing_result important_assignable_parser::process_parsed_result(
	parsing_result result
) const {
	result.node->flags = result.node->flags | ast_node_flag::important;
	return result;
}

}
}
}
