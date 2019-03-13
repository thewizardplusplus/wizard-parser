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
	const auto right_ast = right_parser->parse(tokens);
	return left_ast.node ? left_ast : right_ast;
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
