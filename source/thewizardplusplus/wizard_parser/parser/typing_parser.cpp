#include "typing_parser.hpp"
#include "ast_node.hpp"

namespace thewizardplusplus::wizard_parser::parser {

typing_parser::typing_parser(const std::string& type): type{type} {}

rule_parser::pointer typing_parser::operator=(
	const rule_parser::pointer& parser
) {
	this->parser = parser;
	return shared_from_this();
}

parsing_result typing_parser::parse(const lexer::token_span& tokens) const {
	const auto ast = parser->parse(tokens);
	return ast.node
		? parsing_result{ast_node{type, {}, {*ast.node}}, ast.rest_tokens}
		: parsing_result{{}, ast.rest_tokens};
}

}
