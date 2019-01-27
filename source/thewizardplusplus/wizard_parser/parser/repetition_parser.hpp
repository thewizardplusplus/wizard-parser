#ifndef THEWIZARDPLUSPLUS_WIZARD_PARSER_PARSER_REPETITION_PARSER_HEADER
#define THEWIZARDPLUSPLUS_WIZARD_PARSER_PARSER_REPETITION_PARSER_HEADER

#include "rule_parser.hpp"
#include "../lexer/token.hpp"
#include <cstddef>

namespace thewizardplusplus::wizard_parser::parser {

struct repetition_parser final: rule_parser {
	repetition_parser(
		rule_parser::pointer parser,
		const std::size_t minimal_number,
		const std::size_t maximal_number
	);
	virtual parsing_result parse(
		const lexer::token_span& tokens
	) const override final;

private:
	const rule_parser::pointer parser;
	const std::size_t minimal_number;
	const std::size_t maximal_number;
};

namespace operators {

rule_parser::pointer operator-(rule_parser::pointer parser);
rule_parser::pointer operator*(rule_parser::pointer parser);
rule_parser::pointer operator+(rule_parser::pointer parser);

}
}
#endif
