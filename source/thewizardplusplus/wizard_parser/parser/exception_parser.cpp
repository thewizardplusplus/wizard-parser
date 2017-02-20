#include "exception_parser.hpp"
#include <memory>

using namespace thewizardplusplus::wizard_parser::lexer;

namespace thewizardplusplus {
namespace wizard_parser {
namespace parser {

exception_parser::exception_parser(
	rule_parser::pointer left_parser,
	rule_parser::pointer right_parser
):
	not_sequential_parser{std::move(left_parser), std::move(right_parser)}
{}

std::pair<parsing_result, bool> exception_parser::process_left_result(
	parsing_result result
) const {
	return {std::move(result), result.is_parsed};
}

std::pair<parsing_result, bool> exception_parser::process_right_result(
	parsing_result result
) const {
	return {{false, {}, std::move(result.last_token)}, !result.is_parsed};
}

parsing_result exception_parser::combine_results(
	parsing_result left_result,
	parsing_result right_result,
	const token_group::const_iterator& end
) const {
	static_cast<void>(right_result);
	static_cast<void>(end);

	return left_result;
}

namespace operators {

rule_parser::pointer operator-(
	rule_parser::pointer left_parser,
	rule_parser::pointer right_parser
) {
	return std::make_shared<exception_parser>(
		std::move(left_parser),
		std::move(right_parser)
	);
}

}
}
}
}
