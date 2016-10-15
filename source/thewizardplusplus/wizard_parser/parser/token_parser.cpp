#include "token_parser.hpp"

using namespace lexer;

namespace parser {

parsing_result token_parser::parse(
	const token_group::const_iterator& begin,
	const token_group::const_iterator& end
) const {
	return begin != end ? parse_token(begin) : parse_eoi(end);
}

}
