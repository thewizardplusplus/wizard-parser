#ifndef THEWIZARDPLUSPLUS_WIZARD_PARSER_PARSER_HIDE_PARSER_HEADER
#define THEWIZARDPLUSPLUS_WIZARD_PARSER_PARSER_HIDE_PARSER_HEADER

#include "empty_parser.hpp"
#include "rule_parser.hpp"
#include "parsing_result.hpp"

namespace parser {

struct hide_parser final: empty_parser {
	explicit hide_parser(rule_parser::pointer parser);

protected:
	virtual bool is_empty_result(
		const parsing_result& result
	) const override final;
};

rule_parser::pointer operator&(rule_parser::pointer parser);

}
#endif
