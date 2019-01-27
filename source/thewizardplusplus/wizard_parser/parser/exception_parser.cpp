#include "exception_parser.hpp"
#include <utility>
#include <memory>

namespace thewizardplusplus::wizard_parser::parser {

exception_parser::exception_parser(
	rule_parser::pointer left_parser,
	rule_parser::pointer right_parser
):
	left_parser{std::move(left_parser)},
	right_parser{std::move(right_parser)}
{}

parsing_result exception_parser::parse(const lexer::token_span& tokens) const {
	auto left_ast = left_parser->parse(tokens);
	if (!left_ast.node) {
		return left_ast;
	}

	auto right_ast = right_parser->parse(tokens);
	if (right_ast.node) {
		return {{}, std::move(right_ast.rest_tokens)};
	}

	return left_ast;
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
