#include "dummy_parser.hpp"

namespace thewizardplusplus::wizard_parser::parser {

void dummy_parser::set_parser(rule_parser::weak_pointer parser) {
	this->parser = parser;
}

parsing_result dummy_parser::parse(const lexer::token_span& tokens) const {
	return parser.lock()->parse(tokens);
}

std::shared_ptr<dummy_parser> dummy() {
	return std::make_shared<dummy_parser>();
}

}
