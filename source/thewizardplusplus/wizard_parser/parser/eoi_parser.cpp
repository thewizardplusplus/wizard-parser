#include "eoi_parser.hpp"
#include "ast_node.hpp"
#include <memory>

using namespace thewizardplusplus::wizard_parser::lexer;
using namespace gsl;

namespace thewizardplusplus::wizard_parser::parser {

parsing_result eoi_parser::parse(const span<token>& tokens) const {
	if (!tokens.empty()) {
		return {{}, tokens};
	}

	return {ast_node{"eoi", {}, {}}, {}};
}

rule_parser::pointer eoi() {
	return std::make_shared<eoi_parser>();
}

}
