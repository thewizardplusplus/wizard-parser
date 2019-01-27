#ifndef THEWIZARDPLUSPLUS_WIZARD_PARSER_PARSER_LOOKAHEAD_PARSER_HEADER
#define THEWIZARDPLUSPLUS_WIZARD_PARSER_PARSER_LOOKAHEAD_PARSER_HEADER

#include "rule_parser.hpp"
#include "../lexer/token.hpp"

namespace thewizardplusplus::wizard_parser::parser {

struct lookahead_parser final: rule_parser {
	lookahead_parser(
		const rule_parser::pointer& parser,
		const bool& expected_result
	);
	parsing_result parse(const lexer::token_span& tokens) const override;

private:
	const rule_parser::pointer parser;
	const bool expected_result;
};

namespace operators {

rule_parser::pointer operator&(const rule_parser::pointer& parser);
rule_parser::pointer operator!(const rule_parser::pointer& parser);

}

}
#endif
