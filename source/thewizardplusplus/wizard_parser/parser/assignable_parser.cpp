#include "assignable_parser.hpp"
#include <utility>

using namespace thewizardplusplus::wizard_parser::lexer;
using namespace gsl;

namespace thewizardplusplus {
namespace wizard_parser {
namespace parser {

rule_parser::pointer assignable_parser::operator=(rule_parser::pointer parser) {
	this->parser = std::move(parser);
	return shared_from_this();
}

parsing_result assignable_parser::parse(const span<token>& tokens) const {
	auto ast = parser->parse(tokens);
	if (!ast.node) {
		return ast;
	}

	return process_parsed_result(std::move(ast));
}

}
}
}
