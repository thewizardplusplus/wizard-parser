#include "alternation_parser.hpp"
#include <iterator>
#include <memory>

using namespace thewizardplusplus::wizard_parser::lexer;

namespace thewizardplusplus {
namespace wizard_parser {
namespace parser {

alternation_parser::alternation_parser(
	rule_parser::pointer left_parser,
	rule_parser::pointer right_parser
):
	not_sequential_parser{std::move(left_parser), std::move(right_parser)}
{}

std::pair<parsing_result, bool> alternation_parser::process_left_result(
	parsing_result result
) const {
	return {std::move(result), true};
}

std::pair<parsing_result, bool> alternation_parser::process_right_result(
	parsing_result result
) const {
	return {std::move(result), true};
}

parsing_result alternation_parser::combine_results(
	parsing_result left_result,
	parsing_result right_result
) const {
	if (!left_result.node || !right_result.node) {
		return left_result.node ? left_result : right_result;
	}

	return left_result.get_last_token_offset()
		>= right_result.get_last_token_offset()
		? left_result
		: right_result;
}

namespace operators {

rule_parser::pointer operator|(
	rule_parser::pointer left_parser,
	rule_parser::pointer right_parser
) {
	return std::make_shared<alternation_parser>(
		std::move(left_parser),
		std::move(right_parser)
	);
}

}
}
}
}
