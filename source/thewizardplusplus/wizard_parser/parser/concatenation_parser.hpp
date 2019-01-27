#ifndef THEWIZARDPLUSPLUS_WIZARD_PARSER_PARSER_CONCATENATION_PARSER_HEADER
#define THEWIZARDPLUSPLUS_WIZARD_PARSER_PARSER_CONCATENATION_PARSER_HEADER

#include "rule_parser.hpp"
#include "../lexer/token.hpp"

namespace thewizardplusplus::wizard_parser::parser {

struct concatenation_parser final: rule_parser {
	concatenation_parser(
		rule_parser::pointer left_parser,
		rule_parser::pointer right_parser
	);
	parsing_result parse(const lexer::token_span& tokens) const override;

private:
	const rule_parser::pointer left_parser;
	const rule_parser::pointer right_parser;
};

namespace operators {

rule_parser::pointer operator>>(
	rule_parser::pointer left_parser,
	rule_parser::pointer right_parser
);

}
}
#endif
