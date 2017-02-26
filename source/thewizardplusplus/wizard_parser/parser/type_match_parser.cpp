#include "type_match_parser.hpp"
#include "ast_node.hpp"
#include <utility>
#include <memory>

using namespace thewizardplusplus::wizard_parser::lexer;
using namespace gsl;

namespace thewizardplusplus {
namespace wizard_parser {
namespace parser {

type_match_parser::type_match_parser(std::string sample):
	sample{std::move(sample)}
{}

parsing_result type_match_parser::parse(const span<token>& tokens) const {
	if (tokens.empty()) {
		return {};
	}
	if (tokens[0].type != sample) {
		return {{}, tokens};
	}

	return {ast_node{tokens[0].type, tokens[0].value, {}}, tokens.subspan(1)};
}

namespace operators {

rule_parser::pointer operator""_t(const char* const sample, std::size_t) {
	return std::make_shared<type_match_parser>(sample);
}

}
}
}
}
