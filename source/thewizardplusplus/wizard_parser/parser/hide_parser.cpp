#include "hide_parser.hpp"
#include <utility>
#include <memory>

using namespace thewizardplusplus::wizard_parser::lexer;

namespace thewizardplusplus {
namespace wizard_parser {
namespace parser {

hide_parser::hide_parser(rule_parser::pointer parser):
	empty_parser{std::move(parser)}
{}

bool hide_parser::is_empty_result(const parsing_result& result) const {
	return static_cast<bool>(result.node);
}

namespace operators {

rule_parser::pointer operator&(rule_parser::pointer parser) {
	return std::make_shared<hide_parser>(std::move(parser));
}

}
}
}
}
