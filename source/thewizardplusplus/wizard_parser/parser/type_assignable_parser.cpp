#include "type_assignable_parser.hpp"
#include "ast_node_flag.hpp"
#include <utility>

namespace thewizardplusplus {
namespace wizard_parser {
namespace parser {

type_assignable_parser::type_assignable_parser(std::string type):
	type{std::move(type)}
{}

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
}
}
