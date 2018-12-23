#include "dummy_parser.hpp"
#include <utility>

using namespace thewizardplusplus::wizard_parser::lexer;
using namespace gsl;

namespace thewizardplusplus::wizard_parser::parser {

void dummy_parser::set_parser(rule_parser::weak_pointer parser) {
	this->parser = std::move(parser);
}

parsing_result dummy_parser::parse(const span<token>& tokens) const {
	return parser.lock()->parse(tokens);
}

std::shared_ptr<dummy_parser> dummy() {
	return std::make_shared<dummy_parser>();
}

}
