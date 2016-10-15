#ifndef THEWIZARDPLUSPLUS_WIZARD_PARSER_PARSER_DUMMY_PARSER_HEADER
#define THEWIZARDPLUSPLUS_WIZARD_PARSER_PARSER_DUMMY_PARSER_HEADER

#include "rule_parser.hpp"
#include "../lexer/token_group.hpp"
#include "parsing_result.hpp"

namespace parser {

struct dummy_parser final: rule_parser {
	void set_parser(rule_parser::weak_pointer parser);
	virtual parsing_result parse(
		const lexer::token_group::const_iterator& begin,
		const lexer::token_group::const_iterator& end
	) const override final;

private:
	rule_parser::weak_pointer parser;
};

}
#endif
