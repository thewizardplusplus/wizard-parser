#include "value_match_parser.hpp"
#include <utility>
#include <memory>

using namespace thewizardplusplus::wizard_parser::lexer;

namespace thewizardplusplus {
namespace wizard_parser {
namespace parser {

value_match_parser::value_match_parser(std::string string):
	match_parser{std::move(string)}
{}

bool value_match_parser::is_match(const token& token) const {
	return token.value == sample;
}

namespace operators {

rule_parser::pointer operator""_v(const char* const string, std::size_t) {
	return std::make_shared<value_match_parser>(string);
}

}
}
}
}
