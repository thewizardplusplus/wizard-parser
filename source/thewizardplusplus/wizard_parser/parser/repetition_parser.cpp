#include "repetition_parser.hpp"
#include "common.hpp"
#include "ast_node.hpp"
#include <memory>

namespace thewizardplusplus::wizard_parser::parser {

repetition_parser::repetition_parser(
	const rule_parser::pointer& parser,
	const std::size_t& minimal_number,
	const std::size_t& maximal_number
):
	parser{parser},
	minimal_number{minimal_number},
	maximal_number{maximal_number}
{}

parsing_result repetition_parser::parse(const lexer::token_span& tokens) const {
	const auto [ast, counter] = parse_and_count(tokens);
	return counter < minimal_number || counter > maximal_number
		? parsing_result{{}, tokens}
		: ast;
}

repetition_parser::counted_result repetition_parser::parse_and_count(
	const lexer::token_span& tokens,
	const std::size_t& counter
) const {
	const auto ast = parser->parse(tokens);
	if (!ast.node) {
		return {{ast_node{"sequence", {}, {}}, tokens}, counter};
	}

	auto nodes = ast_node_group{};
	append_node(nodes, *ast.node);

	const auto next_counter = counter + 1;
	const auto [rest_ast, rest_counter] = parse_and_count(
		ast.rest_tokens,
		next_counter
	);
	if (!rest_ast.node) {
		return {{ast_node{"sequence", {}, nodes}, ast.rest_tokens}, next_counter};
	}

	append_node(nodes, *rest_ast.node);

	return {{ast_node{"sequence", {}, nodes}, rest_ast.rest_tokens}, rest_counter};
}

namespace operators {

rule_parser::pointer operator-(const rule_parser::pointer& parser) {
	return std::make_shared<repetition_parser>(parser, 0, 1);
}

rule_parser::pointer operator*(const rule_parser::pointer& parser) {
	return std::make_shared<repetition_parser>(parser, 0, integral_infinity);
}

rule_parser::pointer operator+(const rule_parser::pointer& parser) {
	return std::make_shared<repetition_parser>(parser, 1, integral_infinity);
}

}

}
