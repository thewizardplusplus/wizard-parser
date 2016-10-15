#include "eoi_parser.hpp"

using namespace lexer;

namespace parser {

parsing_result eoi_parser::parse_token(
	const token_group::const_iterator& token
) const {
	return {false, {}, token};
}

parsing_result eoi_parser::parse_eoi(
	const token_group::const_iterator& end
) const {
	return {true, {"eoi", {}, {}}, end};
}

}
