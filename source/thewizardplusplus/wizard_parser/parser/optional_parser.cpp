#include "optional_parser.hpp"
#include <utility>
#include <memory>

using namespace thewizardplusplus::wizard_parser::lexer;

namespace thewizardplusplus {
namespace wizard_parser {
namespace parser {

optional_parser::optional_parser(rule_parser::pointer parser):
	empty_parser{std::move(parser)}
{}

bool optional_parser::is_empty_result(const parsing_result& result) const {
	return !result.node;
}

namespace operators {

rule_parser::pointer operator-(rule_parser::pointer parser) {
	return std::make_shared<optional_parser>(std::move(parser));
}

}
}
}
}
