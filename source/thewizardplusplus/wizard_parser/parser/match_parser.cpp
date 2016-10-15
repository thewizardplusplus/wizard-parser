#include "match_parser.hpp"
#include <utility>
#include <iterator>

using namespace lexer;

namespace parser {

match_parser::match_parser(std::string sample):
	sample{std::move(sample)}
{}

parsing_result match_parser::parse_token(
	const token_group::const_iterator& token
) const {
	if (!is_match(*token)) {
		return {false, {}, token};
	}

	return {true, {token->type, token->value, {}}, std::next(token)};
}

parsing_result match_parser::parse_eoi(
	const token_group::const_iterator& end
) const {
	return {false, {}, end};
}

}
