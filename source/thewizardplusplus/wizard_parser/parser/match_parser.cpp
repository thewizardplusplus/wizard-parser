#include "match_parser.hpp"
#include "ast_node.hpp"
#include <utility>

using namespace thewizardplusplus::wizard_parser::lexer;
using namespace gsl;

namespace thewizardplusplus {
namespace wizard_parser {
namespace parser {

match_parser::match_parser(std::string sample):
	sample{std::move(sample)}
{}

parsing_result match_parser::parse_token(const span<token>& tokens) const {
	if (!is_match(tokens[0])) {
		return {{}, tokens};
	}

	return {ast_node{tokens[0].type, tokens[0].value, {}}, tokens.subspan(1)};
}

parsing_result match_parser::parse_eoi() const {
	return {};
}

}
}
}
