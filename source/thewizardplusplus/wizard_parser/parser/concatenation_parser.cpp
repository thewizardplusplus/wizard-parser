#include "concatenation_parser.hpp"
#include "common.hpp"
#include "ast_node.hpp"
#include <memory>

namespace thewizardplusplus::wizard_parser::parser {

concatenation_parser::concatenation_parser(
	const rule_parser::pointer& left_parser,
	const rule_parser::pointer& right_parser
):
	left_parser{left_parser},
	right_parser{right_parser}
{}

parsing_result concatenation_parser::parse(
	const lexer::token_span& tokens
) const {
	const auto left_ast = left_parser->parse(tokens);
	if (!left_ast.node) {
		return left_ast;
	}

	const auto right_ast = right_parser->parse(left_ast.rest_tokens);
	if (!right_ast.node) {
		return right_ast;
	}

	auto nodes = ast_node_group{};
	append_node(nodes, *left_ast.node);
	append_node(nodes, *right_ast.node);

	const auto type = (+ast_node_type::sequence)._to_string();
	return {ast_node{type, {}, nodes}, right_ast.rest_tokens};
}

namespace operators {

rule_parser::pointer operator>>(
	const rule_parser::pointer& left_parser,
	const rule_parser::pointer& right_parser
) {
	return std::make_shared<concatenation_parser>(left_parser, right_parser);
}

}

}
