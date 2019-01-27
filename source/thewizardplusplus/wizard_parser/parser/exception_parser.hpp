#ifndef THEWIZARDPLUSPLUS_WIZARD_PARSER_PARSER_EXCEPTION_PARSER_HEADER
#define THEWIZARDPLUSPLUS_WIZARD_PARSER_PARSER_EXCEPTION_PARSER_HEADER

#include "rule_parser.hpp"
#include "../lexer/token.hpp"

namespace thewizardplusplus::wizard_parser::parser {

struct exception_parser final: rule_parser {
	exception_parser(
		const rule_parser::pointer& left_parser,
		const rule_parser::pointer& right_parser
	);
	parsing_result parse(const lexer::token_span& tokens) const override;

private:
	const rule_parser::pointer left_parser;
	const rule_parser::pointer right_parser;
};

namespace operators {

rule_parser::pointer operator-(
	const rule_parser::pointer& left_parser,
	const rule_parser::pointer& right_parser
);

}

}
#endif
