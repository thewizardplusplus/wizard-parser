#include "empty_parser.hpp"
#include "ast_node.hpp"
#include <utility>

namespace thewizardplusplus {
namespace wizard_parser {
namespace parser {

empty_parser::empty_parser(rule_parser::pointer parser):
	wrapping_parser{std::move(parser)}
{}

parsing_result empty_parser::process_result(parsing_result result) const {
	return is_empty_result(result)
		? parsing_result{
			ast_node{"nothing", {}, {}},
			std::move(result.rest_tokens)
		}
		: result;
}

}
}
}
