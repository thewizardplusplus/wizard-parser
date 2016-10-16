#include "eoi_parser.hpp"
#include <memory>

using namespace thewizardplusplus::wizard_parser::lexer;

namespace thewizardplusplus {
namespace wizard_parser {
namespace parser {

parsing_result eoi_parser::parse_token(
	const token_group::const_iterator& token
) const {
	return {false, {}, token};
}

parsing_result eoi_parser::parse_eoi(
	const token_group::const_iterator& end
) const {
	return {true, {"eoi", {}, {}}, end};
}

rule_parser::pointer eoi() {
	return std::make_shared<eoi_parser>();
}

}
}
}
