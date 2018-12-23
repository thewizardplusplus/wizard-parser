#include "concatenation_parser.hpp"
#include "utilities.hpp"
#include "ast_node.hpp"
#include <utility>
#include <vector>
#include <memory>

using namespace thewizardplusplus::wizard_parser::lexer;
using namespace gsl;

namespace thewizardplusplus::wizard_parser::parser {

concatenation_parser::concatenation_parser(
	rule_parser::pointer left_parser,
	rule_parser::pointer right_parser
):
	left_parser{std::move(left_parser)},
	right_parser{std::move(right_parser)}
{}

parsing_result concatenation_parser::parse(const span<token>& tokens) const {
	auto left_ast = left_parser->parse(tokens);
	if (!left_ast.node) {
		return left_ast;
	}

	auto right_ast = right_parser->parse(left_ast.rest_tokens);
	if (!right_ast.node) {
		return right_ast;
	}

	auto nodes = std::vector<ast_node>{};
	append_node(nodes, std::move(*left_ast.node));
	append_node(nodes, std::move(*right_ast.node));

	return {
		ast_node{"sequence", {}, std::move(nodes)},
		std::move(right_ast.rest_tokens)
	};
}

namespace operators {

rule_parser::pointer operator>>(
	rule_parser::pointer left_parser,
	rule_parser::pointer right_parser
) {
	return std::make_shared<concatenation_parser>(
		std::move(left_parser),
		std::move(right_parser)
	);
}

}
}
