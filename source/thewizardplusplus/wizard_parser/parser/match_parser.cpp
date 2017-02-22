#include "match_parser.hpp"
#include "ast_node.hpp"
#include <utility>
#include <iterator>

using namespace thewizardplusplus::wizard_parser::lexer;

namespace thewizardplusplus {
namespace wizard_parser {
namespace parser {

match_parser::match_parser(std::string sample):
	sample{std::move(sample)}
{}

parsing_result match_parser::parse_token(
	const token_group::const_iterator& token
) const {
	if (!is_match(*token)) {
		return {{}, token};
	}

	return {ast_node{token->type, token->value, {}}, std::next(token)};
}

parsing_result match_parser::parse_eoi(
	const token_group::const_iterator& end
) const {
	return {{}, end};
}

}
}
}
