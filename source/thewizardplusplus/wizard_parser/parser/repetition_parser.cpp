#include "repetition_parser.hpp"
#include "utilities.hpp"
#include "ast_node.hpp"
#include <utility>
#include <list>
#include <memory>

using namespace thewizardplusplus::wizard_parser::lexer;

namespace thewizardplusplus {
namespace wizard_parser {
namespace parser {

repetition_parser::repetition_parser(rule_parser::pointer parser):
	parser{std::move(parser)}
{}

parsing_result repetition_parser::parse(
	const token_group::const_iterator& begin,
	const token_group::const_iterator& end
) const {
	auto nodes = std::list<ast_node>{};
	auto start = begin;
	while (true) {
		auto ast = parser->parse(start, end);
		if (!ast.node) {
			break;
		}

		append_node(nodes, std::move(*ast.node));
		start = ast.last_token;
	}

	return {ast_node{"sequence", {}, std::move(nodes)}, start};
}

namespace operators {

rule_parser::pointer operator*(rule_parser::pointer parser) {
	return std::make_shared<repetition_parser>(std::move(parser));
}

}
}
}
}
