#include "empty_parser.hpp"
#include "ast_node.hpp"
#include <memory>

using namespace thewizardplusplus::wizard_parser::lexer;
using namespace gsl;

namespace thewizardplusplus {
namespace wizard_parser {
namespace parser {

parsing_result empty_parser::parse(const span<token>& tokens) const {
	return {ast_node{"nothing", {}, {}}, tokens};
}

rule_parser::pointer empty() {
	return std::make_shared<empty_parser>();
}

}
}
}
