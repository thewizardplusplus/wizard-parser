#include "eoi_parser.hpp"
#include "ast_node.hpp"
#include <memory>

using namespace thewizardplusplus::wizard_parser::lexer;
using namespace gsl;

namespace thewizardplusplus {
namespace wizard_parser {
namespace parser {

parsing_result eoi_parser::parse_token(const span<token>& tokens) const {
	return {{}, tokens};
}

parsing_result eoi_parser::parse_eoi() const {
	return {ast_node{"eoi", {}, {}}, {}};
}

rule_parser::pointer eoi() {
	return std::make_shared<eoi_parser>();
}

}
}
}
