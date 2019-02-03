#include "type_assignable_parser.hpp"
#include "ast_node.hpp"

namespace thewizardplusplus::wizard_parser::parser {

type_assignable_parser::type_assignable_parser(const std::string& type):
	type{type}
{}

rule_parser::pointer type_assignable_parser::operator=(
	const rule_parser::pointer& parser
) {
	this->parser = parser;
	return shared_from_this();
}

parsing_result type_assignable_parser::parse(
	const lexer::token_span& tokens
) const {
	const auto ast = parser->parse(tokens);
	if (!ast.node || ast.node->flags & ast_node_flag::named) {
		return ast;
	}

	auto ast_copy = ast;
	ast_copy.node->type = type;
	ast_copy.node->flags = ast.node->flags | ast_node_flag::named;

	return ast_copy;
}

}
