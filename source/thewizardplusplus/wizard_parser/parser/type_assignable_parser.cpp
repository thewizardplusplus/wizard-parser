#include "type_assignable_parser.hpp"
#include "ast_node_flag.hpp"
#include <utility>

using namespace thewizardplusplus::wizard_parser::lexer;
using namespace gsl;

namespace thewizardplusplus {
namespace wizard_parser {
namespace parser {

type_assignable_parser::type_assignable_parser(std::string type):
	type{std::move(type)}
{}

rule_parser::pointer type_assignable_parser::operator=(
	rule_parser::pointer parser
) {
	this->parser = std::move(parser);
	return shared_from_this();
}

parsing_result type_assignable_parser::parse(const span<token>& tokens) const {
	auto ast = parser->parse(tokens);
	if (!ast.node || ast.node->flags & ast_node_flag::named) {
		return ast;
	}

	ast.node->type = type;
	ast.node->flags = ast.node->flags | ast_node_flag::named;

	return ast;
}

}
}
}
