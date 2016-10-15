#ifndef PARSER_EOI_PARSER_HEADER
#define PARSER_EOI_PARSER_HEADER

#include "token_parser.hpp"
#include "../lexer/token_group.hpp"
#include "parsing_result.hpp"

namespace parser {

struct eoi_parser final: token_parser {
protected:
	virtual parsing_result parse_token(
		const lexer::token_group::const_iterator& token
	) const override final;
	virtual parsing_result parse_eoi(
		const lexer::token_group::const_iterator& end
	) const override final;
};

}
#endif
