#ifndef THEWIZARDPLUSPLUS_WIZARD_PARSER_PARSER_TOKEN_PARSER_HEADER
#define THEWIZARDPLUSPLUS_WIZARD_PARSER_PARSER_TOKEN_PARSER_HEADER

#include "rule_parser.hpp"
#include "../lexer/token_group.hpp"
#include "parsing_result.hpp"

namespace parser {

struct token_parser: rule_parser {
	virtual parsing_result parse(
		const lexer::token_group::const_iterator& begin,
		const lexer::token_group::const_iterator& end
	) const override final;

protected:
	virtual parsing_result parse_token(
		const lexer::token_group::const_iterator& token
	) const = 0;
	virtual parsing_result parse_eoi(
		const lexer::token_group::const_iterator& end
	) const = 0;
};

}
#endif
