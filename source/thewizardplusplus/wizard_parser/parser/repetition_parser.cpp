#include "repetition_parser.hpp"
#include "common.hpp"
#include "ast_node.hpp"
#include <memory>

namespace thewizardplusplus::wizard_parser::parser {

repetition_parser::repetition_parser(
	rule_parser::pointer parser,
	const std::size_t minimal_number,
	const std::size_t maximal_number
):
	parser{parser},
	minimal_number{minimal_number},
	maximal_number{maximal_number}
{}

parsing_result repetition_parser::parse(const lexer::token_span& tokens) const {
	auto nodes = ast_node_group{};
	auto rest_tokens = tokens;
	auto repetition_number = std::size_t{};
	for (; repetition_number < maximal_number; ++repetition_number) {
		const auto ast = parser->parse(rest_tokens);
		if (!ast.node) {
			break;
		}

		append_node(nodes, *ast.node);
		rest_tokens = ast.rest_tokens;
	}
	if (
		repetition_number < minimal_number
		|| repetition_number > maximal_number
	) {
		return {{}, tokens};
	}

	return {ast_node{"sequence", {}, nodes}, rest_tokens};
}

namespace operators {

rule_parser::pointer operator-(rule_parser::pointer parser) {
	return std::make_shared<repetition_parser>(parser, 0, 1);
}

rule_parser::pointer operator*(rule_parser::pointer parser) {
	return std::make_shared<repetition_parser>(parser, 0, integral_infinity);
}

rule_parser::pointer operator+(rule_parser::pointer parser) {
	return std::make_shared<repetition_parser>(parser, 1, integral_infinity);
}

}

}
