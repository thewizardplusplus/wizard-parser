#include "lookahead_parser.hpp"
#include <memory>

namespace thewizardplusplus::wizard_parser::parser {

lookahead_parser::lookahead_parser(
	const rule_parser::pointer& parser,
	const bool& expected_result
):
	parser{parser},
	expected_result{expected_result}
{}

parsing_result lookahead_parser::parse(const lexer::token_span& tokens) const {
	const auto ast = parser->parse(tokens);
	if (static_cast<bool>(ast.node) != expected_result) {
		return {{}, ast.rest_tokens};
	}

	return {ast_node{"nothing", {}, {}}, ast.rest_tokens};
}

namespace operators {

rule_parser::pointer operator&(const rule_parser::pointer& parser) {
	return std::make_shared<lookahead_parser>(parser, true);
}

rule_parser::pointer operator!(const rule_parser::pointer& parser) {
	return std::make_shared<lookahead_parser>(parser, false);
}

}

}
