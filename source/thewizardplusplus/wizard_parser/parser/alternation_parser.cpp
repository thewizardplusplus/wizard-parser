#include "alternation_parser.hpp"
#include <utility>
#include <memory>

using namespace thewizardplusplus::wizard_parser::lexer;
using namespace gsl;

namespace thewizardplusplus::wizard_parser::parser {

alternation_parser::alternation_parser(
	rule_parser::pointer left_parser,
	rule_parser::pointer right_parser
):
	left_parser{std::move(left_parser)},
	right_parser{std::move(right_parser)}
{}

parsing_result alternation_parser::parse(const span<token>& tokens) const {
	const auto left_ast = left_parser->parse(tokens);
	const auto right_ast = right_parser->parse(tokens);
	if (!left_ast.node || !right_ast.node) {
		return left_ast.node ? left_ast : right_ast;
	}

	return left_ast.get_last_token_offset()
		>= right_ast.get_last_token_offset()
		? left_ast
		: right_ast;
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
