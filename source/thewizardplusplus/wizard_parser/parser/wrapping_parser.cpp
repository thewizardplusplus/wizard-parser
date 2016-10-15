#include "wrapping_parser.hpp"
#include <utility>

using namespace thewizardplusplus::wizard_parser::lexer;

namespace thewizardplusplus {
namespace wizard_parser {
namespace parser {

wrapping_parser::wrapping_parser(rule_parser::pointer parser):
	parser{std::move(parser)}
{}

parsing_result wrapping_parser::parse(
	const token_group::const_iterator& begin,
	const token_group::const_iterator& end
) const {
	auto ast = parser->parse(begin, end);
	return process_result(std::move(ast));
}

}
}
}
