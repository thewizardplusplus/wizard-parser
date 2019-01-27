#include "assignable_parser.hpp"

namespace thewizardplusplus::wizard_parser::parser {

rule_parser::pointer assignable_parser::operator=(rule_parser::pointer parser) {
	this->parser = parser;
	return shared_from_this();
}

parsing_result assignable_parser::parse(const lexer::token_span& tokens) const {
	const auto ast = parser->parse(tokens);
	if (!ast.node) {
		return ast;
	}

	return process_parsed_result(ast);
}

}
