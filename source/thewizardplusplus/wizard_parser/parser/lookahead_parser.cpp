#include "lookahead_parser.hpp"
#include <utility>
#include <memory>

using namespace thewizardplusplus::wizard_parser::lexer;
using namespace gsl;

namespace thewizardplusplus::wizard_parser::parser {

lookahead_parser::lookahead_parser(
	rule_parser::pointer parser,
	const bool expected_result
):
	parser{std::move(parser)},
	expected_result{expected_result}
{}

parsing_result lookahead_parser::parse(const span<token>& tokens) const {
	auto ast = parser->parse(tokens);
	if (static_cast<bool>(ast.node) != expected_result) {
		return {{}, std::move(ast.rest_tokens)};
	}

	return {ast_node{"nothing", {}, {}}, std::move(ast.rest_tokens)};
}

namespace operators {

rule_parser::pointer operator&(rule_parser::pointer parser) {
	return std::make_shared<lookahead_parser>(std::move(parser), true);
}

rule_parser::pointer operator!(rule_parser::pointer parser) {
	return std::make_shared<lookahead_parser>(std::move(parser), false);
}

}
}
