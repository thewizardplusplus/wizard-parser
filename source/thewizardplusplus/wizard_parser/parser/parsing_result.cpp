#include "parsing_result.hpp"
#include <limits>

using namespace lexer;

namespace parser {

std::size_t parsing_result::get_last_token_offset(
	const token_group::const_iterator& end
) const {
	return this->last_token != end
		? this->last_token->offset
		: std::numeric_limits<std::size_t>::max();
}

}
