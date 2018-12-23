#ifndef THEWIZARDPLUSPLUS_WIZARD_PARSER_PARSER_LOOKAHEAD_PARSER_HEADER
#define THEWIZARDPLUSPLUS_WIZARD_PARSER_PARSER_LOOKAHEAD_PARSER_HEADER

#include "rule_parser.hpp"
#include "../lexer/token.hpp"
#include "parsing_result.hpp"
#include "../vendor/gsl/span.hpp"

namespace thewizardplusplus::wizard_parser::parser {

struct lookahead_parser final: rule_parser {
	lookahead_parser(rule_parser::pointer parser, const bool expected_result);
	parsing_result parse(const gsl::span<lexer::token>& tokens) const override;

private:
	const rule_parser::pointer parser;
	const bool expected_result;
};

namespace operators {

rule_parser::pointer operator&(rule_parser::pointer parser);
rule_parser::pointer operator!(rule_parser::pointer parser);

}
}
#endif
