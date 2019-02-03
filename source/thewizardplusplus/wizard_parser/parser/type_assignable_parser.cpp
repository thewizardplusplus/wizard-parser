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
	return ast.node
		? parsing_result{ast_node{type, {}, {*ast.node}}, ast.rest_tokens}
		: ast;
}

}
