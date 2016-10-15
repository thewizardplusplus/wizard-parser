#ifndef THEWIZARDPLUSPLUS_WIZARD_PARSER_PARSER_WRAPPING_PARSER_HEADER
#define THEWIZARDPLUSPLUS_WIZARD_PARSER_PARSER_WRAPPING_PARSER_HEADER

#include "rule_parser.hpp"
#include "../lexer/token_group.hpp"
#include "parsing_result.hpp"

namespace parser {

struct wrapping_parser: rule_parser {
	wrapping_parser() = default;
	explicit wrapping_parser(rule_parser::pointer parser);
	virtual parsing_result parse(
		const lexer::token_group::const_iterator& begin,
		const lexer::token_group::const_iterator& end
	) const override final;

protected:
	rule_parser::pointer parser;

	virtual parsing_result process_result(parsing_result result) const = 0;
};

}
#endif
