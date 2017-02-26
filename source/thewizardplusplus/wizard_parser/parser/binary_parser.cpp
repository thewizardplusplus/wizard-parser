#include "binary_parser.hpp"

using namespace thewizardplusplus::wizard_parser::lexer;
using namespace gsl;

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

parsing_result binary_parser::parse(const span<token>& tokens) const {
	auto left_ast = left_parser->parse(tokens);
	auto processed_left_ast = process_left_result(std::move(left_ast));
	if (!processed_left_ast.second) {
		return processed_left_ast.first;
	}

	const auto rest_tokens = is_sequential()
		? processed_left_ast.first.rest_tokens
		: tokens;
	auto right_ast = right_parser->parse(rest_tokens);
	auto processed_right_ast = process_right_result(std::move(right_ast));
	if (!processed_right_ast.second) {
		return processed_right_ast.first;
	}

	return combine_results(
		std::move(processed_left_ast.first),
		std::move(processed_right_ast.first)
	);
}

}
}
}
