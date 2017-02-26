#include "value_match_parser.hpp"
#include "ast_node.hpp"
#include <utility>
#include <memory>

using namespace thewizardplusplus::wizard_parser::lexer;
using namespace gsl;

namespace thewizardplusplus {
namespace wizard_parser {
namespace parser {

value_match_parser::value_match_parser(std::string sample):
	sample{std::move(sample)}
{}

parsing_result value_match_parser::parse(const span<token>& tokens) const {
	if (tokens.empty()) {
		return {};
	}
	if (tokens[0].value != sample) {
		return {{}, tokens};
	}

	return {ast_node{tokens[0].type, tokens[0].value, {}}, tokens.subspan(1)};
}

namespace operators {

rule_parser::pointer operator""_v(const char* const sample, std::size_t) {
	return std::make_shared<value_match_parser>(sample);
}

}
}
}
}
