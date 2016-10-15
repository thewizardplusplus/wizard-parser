#ifndef THEWIZARDPLUSPLUS_WIZARD_PARSER_PARSER_EXCEPTION_PARSER_HEADER
#define THEWIZARDPLUSPLUS_WIZARD_PARSER_PARSER_EXCEPTION_PARSER_HEADER

#include "not_sequential_parser.hpp"
#include "rule_parser.hpp"
#include "parsing_result.hpp"
#include <utility>

namespace parser {

struct exception_parser final: not_sequential_parser {
	exception_parser(
		rule_parser::pointer left_parser,
		rule_parser::pointer right_parser
	);

protected:
	virtual std::pair<parsing_result, bool> process_left_result(
		parsing_result result
	) const override final;
	virtual std::pair<parsing_result, bool> process_right_result(
		parsing_result result
	) const override final;
	virtual parsing_result combine_results(
		parsing_result left_result,
		parsing_result right_result,
		const lexer::token_group::const_iterator& end
	) const override final;
};

rule_parser::pointer operator-(
	rule_parser::pointer left_parser,
	rule_parser::pointer right_parser
);

}
#endif
