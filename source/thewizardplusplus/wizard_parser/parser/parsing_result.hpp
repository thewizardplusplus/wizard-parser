#ifndef PARSER_PARSING_RESULT_HEADER
#define PARSER_PARSING_RESULT_HEADER

#include "ast_node.hpp"
#include "../lexer/token_group.hpp"
#include <cstddef>

namespace parser {

struct parsing_result {
	bool is_parsed;
	ast_node node;
	lexer::token_group::const_iterator last_token;

	std::size_t get_last_token_offset(
		const lexer::token_group::const_iterator& end
	) const;
};

}
#endif
