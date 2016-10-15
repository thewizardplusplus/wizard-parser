#ifndef THEWIZARDPLUSPLUS_WIZARD_PARSER_PARSER_MATCH_PARSER_HEADER
#define THEWIZARDPLUSPLUS_WIZARD_PARSER_PARSER_MATCH_PARSER_HEADER

#include "token_parser.hpp"
#include "../lexer/token_group.hpp"
#include "parsing_result.hpp"
#include "../lexer/token.hpp"
#include <string>

namespace parser {

struct match_parser: token_parser {
	explicit match_parser(std::string sample);

protected:
	const std::string sample;

	virtual parsing_result parse_token(
		const lexer::token_group::const_iterator& token
	) const override final;
	virtual parsing_result parse_eoi(
		const lexer::token_group::const_iterator& end
	) const override final;
	virtual bool is_match(const lexer::token& token) const = 0;
};

}
#endif
