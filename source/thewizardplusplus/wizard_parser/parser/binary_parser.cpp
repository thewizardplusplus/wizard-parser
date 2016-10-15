#include "binary_parser.hpp"

using namespace thewizardplusplus::wizard_parser::lexer;

namespace thewizardplusplus {
namespace wizard_parser {
namespace parser {

binary_parser::binary_parser(
	rule_parser::pointer left_parser,
	rule_parser::pointer right_parser
):
	left_parser{std::move(left_parser)},
	right_parser{std::move(right_parser)}
{}

parsing_result binary_parser::parse(
	const token_group::const_iterator& begin,
	const token_group::const_iterator& end
) const {
	auto left_ast = left_parser->parse(begin, end);
	auto processed_left_ast = process_left_result(std::move(left_ast));
	if (!processed_left_ast.second) {
		return processed_left_ast.first;
	}

	const auto next_begin = is_sequential()
		? processed_left_ast.first.last_token
		: begin;
	auto right_ast = right_parser->parse(next_begin, end);
	auto processed_right_ast = process_right_result(std::move(right_ast));
	if (!processed_right_ast.second) {
		return processed_right_ast.first;
	}

	return combine_results(
		std::move(processed_left_ast.first),
		std::move(processed_right_ast.first),
		end
	);
}

}
}
}
