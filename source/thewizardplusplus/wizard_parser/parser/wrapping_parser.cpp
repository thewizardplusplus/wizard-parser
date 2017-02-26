#include "wrapping_parser.hpp"
#include <utility>

using namespace thewizardplusplus::wizard_parser::lexer;
using namespace gsl;

namespace thewizardplusplus {
namespace wizard_parser {
namespace parser {

wrapping_parser::wrapping_parser(rule_parser::pointer parser):
	parser{std::move(parser)}
{}

parsing_result wrapping_parser::parse(const span<token>& tokens) const {
	auto ast = parser->parse(tokens);
	return process_result(std::move(ast));
}

}
}
}
