#include "repetition_parser.hpp"
#include "utilities.hpp"
#include "ast_node.hpp"
#include <utility>
#include <vector>
#include <memory>
#include <limits>

using namespace thewizardplusplus::wizard_parser::lexer;
using namespace gsl;

namespace thewizardplusplus::wizard_parser::parser {

repetition_parser::repetition_parser(
	rule_parser::pointer parser,
	const std::size_t minimal_number,
	const std::size_t maximal_number
):
	parser{std::move(parser)},
	minimal_number{minimal_number},
	maximal_number{maximal_number}
{}

parsing_result repetition_parser::parse(const span<token>& tokens) const {
	auto nodes = std::vector<ast_node>{};
	auto rest_tokens = tokens;
	auto repetition_number = std::size_t{};
	for (; repetition_number < maximal_number; ++repetition_number) {
		auto ast = parser->parse(rest_tokens);
		if (!ast.node) {
			break;
		}

		append_node(nodes, std::move(*ast.node));
		rest_tokens = std::move(ast.rest_tokens);
	}
	if (
		repetition_number < minimal_number
		|| repetition_number > maximal_number
	) {
		return {{}, std::move(tokens)};
	}

	return {ast_node{"sequence", {}, std::move(nodes)}, std::move(rest_tokens)};
}

rule_parser::pointer rep(
	rule_parser::pointer parser,
	const std::size_t minimal_number,
	const std::size_t maximal_number
) {
	return std::make_shared<repetition_parser>(
		std::move(parser),
		minimal_number,
		maximal_number
	);
}

namespace operators {

rule_parser::pointer operator-(rule_parser::pointer parser) {
	return rep(std::move(parser), 0, 1);
}

rule_parser::pointer operator*(
	rule_parser::pointer parser,
	const std::size_t number
) {
	return rep(std::move(parser), number, number);
}

rule_parser::pointer operator*(rule_parser::pointer parser) {
	return rep(std::move(parser), 0, std::numeric_limits<std::size_t>::max());
}

rule_parser::pointer operator+(rule_parser::pointer parser) {
	return rep(std::move(parser), 1, std::numeric_limits<std::size_t>::max());
}

}
}
