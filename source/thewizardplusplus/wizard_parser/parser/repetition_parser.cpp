#include "repetition_parser.hpp"
#include "utilities.hpp"
#include "ast_node.hpp"
#include <utility>
#include <list>
#include <memory>

using namespace thewizardplusplus::wizard_parser::lexer;
using namespace gsl;

namespace thewizardplusplus {
namespace wizard_parser {
namespace parser {

repetition_parser::repetition_parser(rule_parser::pointer parser):
	parser{std::move(parser)}
{}

parsing_result repetition_parser::parse(const span<token>& tokens) const {
	auto nodes = std::list<ast_node>{};
	auto rest_tokens = tokens;
	while (true) {
		auto ast = parser->parse(rest_tokens);
		if (!ast.node) {
			break;
		}

		append_node(nodes, std::move(*ast.node));
		rest_tokens = std::move(ast.rest_tokens);
	}

	return {ast_node{"sequence", {}, std::move(nodes)}, std::move(rest_tokens)};
}

namespace operators {

rule_parser::pointer operator*(rule_parser::pointer parser) {
	return std::make_shared<repetition_parser>(std::move(parser));
}

}
}
}
}
