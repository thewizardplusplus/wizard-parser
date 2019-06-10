#include "repetition_parser.hpp"
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
	// if not enough repetitions, return an offset of a first nonmatch
	return counter >= minimal_number ? ast : parsing_result{{}, ast.rest_tokens};
}

repetition_parser::counted_result repetition_parser::parse_and_count(
	const lexer::token_span& tokens,
	const std::size_t& counter
) const {
	const auto type = (+ast_node_type::sequence)._to_string();
	const auto final_result = counted_result{
		{ast_node{type, {}, {}, lexer::get_offset(tokens)}, tokens},
		counter
	};
	if (counter >= maximal_number) {
		return final_result;
	}

	const auto ast = parser->parse(tokens);
	if (!ast.node) {
		return final_result;
	}

	const auto [rest_ast, rest_counter] = parse_and_count(
		ast.rest_tokens,
		counter+1
	);
	return {
		{ast_node{type, {}, {*ast.node, *rest_ast.node}}, rest_ast.rest_tokens},
		rest_counter
	};
}

namespace operators {

rule_parser::pointer operator-(const rule_parser::pointer& parser) {
	return std::make_shared<repetition_parser>(parser, 0, 1);
}

rule_parser::pointer operator*(const rule_parser::pointer& parser) {
	return std::make_shared<repetition_parser>(parser);
}

rule_parser::pointer operator+(const rule_parser::pointer& parser) {
	return std::make_shared<repetition_parser>(parser, 1);
}

}

}
