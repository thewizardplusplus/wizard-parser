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
	const auto type = (+ast_node_type::nothing)._to_string();
	const auto ast = parser->parse(tokens);
	// if a match is expected, return rest tokens from its result
	// (i.e. an offset or after a match, or before its unexpected token)
	//
	// if a nonmatch is expected, return rest tokens without additional one
	// (i.e. a current offset and for further parsing,
	// and as an unexpected token position)
	const auto rest_tokens = expected_result ? ast.rest_tokens : tokens;
	return ast.node.has_value() == expected_result
		? parsing_result{
			ast_node{type, {}, {}, lexer::get_offset(tokens)},
			rest_tokens
		}
		: parsing_result{{}, rest_tokens};
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
