#include "lift_parser.hpp"
#include "ast_node_flag.hpp"
#include <utility>

using namespace thewizardplusplus::wizard_parser::lexer;
using namespace gsl;

namespace thewizardplusplus {
namespace wizard_parser {
namespace parser {

rule_parser::pointer lift_parser::operator=(rule_parser::pointer parser) {
	this->parser = std::move(parser);
	return shared_from_this();
}

parsing_result lift_parser::parse(const span<token>& tokens) const {
	auto ast = parser->parse(tokens);
	if (
		!ast.node
		|| ast.node->flags & ast_node_flag::important
		|| ast.node->children.size() != 1
	) {
		return ast;
	}

	return {std::move(ast.node->children.front()), std::move(ast.rest_tokens)};
}

}
}
}
