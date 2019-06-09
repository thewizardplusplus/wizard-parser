#include "exception_parser.hpp"
#include <memory>

namespace thewizardplusplus::wizard_parser::parser {

exception_parser::exception_parser(
	const rule_parser::pointer& left_parser,
	const rule_parser::pointer& right_parser
):
	left_parser{left_parser},
	right_parser{right_parser}
{}

parsing_result exception_parser::parse(const lexer::token_span& tokens) const {
	const auto left_ast = left_parser->parse(tokens);
	if (!left_ast.node) {
		return {{}, left_ast.rest_tokens};
	}

	// there should be no a match by the right parser at a current offset,
	// so rest tokens are returns without additional one
	const auto right_ast = right_parser->parse(tokens);
	if (right_ast.node) {
		return {{}, tokens};
	}

	return left_ast;
}

namespace operators {

rule_parser::pointer operator-(
	const rule_parser::pointer& left_parser,
	const rule_parser::pointer& right_parser
) {
	return std::make_shared<exception_parser>(left_parser, right_parser);
}

}

}
