#include "alternation_parser.hpp"
#include <memory>

namespace thewizardplusplus::wizard_parser::parser {

alternation_parser::alternation_parser(
	const rule_parser::pointer& left_parser,
	const rule_parser::pointer& right_parser
):
	left_parser{left_parser},
	right_parser{right_parser}
{}

parsing_result alternation_parser::parse(
	const lexer::token_span& tokens
) const {
	const auto left_ast = left_parser->parse(tokens);
	if (left_ast.node) {
		return left_ast;
	}

	const auto right_ast = right_parser->parse(tokens);
	if (right_ast.node) {
		return right_ast;
	}

	// return a maximal offset, to which tokens can be parsed
	const auto left_rest_offset = lexer::get_offset(left_ast.rest_tokens);
	const auto right_rest_offset = lexer::get_offset(right_ast.rest_tokens);
	return left_rest_offset >= right_rest_offset
		? parsing_result{{}, left_ast.rest_tokens}
		: parsing_result{{}, right_ast.rest_tokens};
}

namespace operators {

rule_parser::pointer operator|(
	const rule_parser::pointer& left_parser,
	const rule_parser::pointer& right_parser
) {
	return std::make_shared<alternation_parser>(left_parser, right_parser);
}

}

}
