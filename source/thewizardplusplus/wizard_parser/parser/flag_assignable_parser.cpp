#include "flag_assignable_parser.hpp"

namespace thewizardplusplus {
namespace wizard_parser {
namespace parser {

flag_assignable_parser::flag_assignable_parser(const ast_node_flag flag):
	flag{flag}
{}

parsing_result flag_assignable_parser::process_parsed_result(
	parsing_result result
) const {
	result.node.flags = result.node.flags | flag;
	return result;
}

}
}
}
