#include "dummy_parser.hpp"
#include <utility>

using namespace thewizardplusplus::wizard_parser::lexer;

namespace thewizardplusplus {
namespace wizard_parser {
namespace parser {

void dummy_parser::set_parser(rule_parser::weak_pointer parser) {
	this->parser = std::move(parser);
}

parsing_result dummy_parser::parse(
	const token_group::const_iterator& begin,
	const token_group::const_iterator& end
) const {
	return parser.lock()->parse(begin, end);
}

}
}
}
