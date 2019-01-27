#ifndef THEWIZARDPLUSPLUS_WIZARD_PARSER_PARSER_EMPTY_PARSER_HEADER
#define THEWIZARDPLUSPLUS_WIZARD_PARSER_PARSER_EMPTY_PARSER_HEADER

#include "rule_parser.hpp"
#include "../lexer/token.hpp"
#include "parsing_result.hpp"

namespace thewizardplusplus::wizard_parser::parser {

struct empty_parser final: rule_parser {
	parsing_result parse(const lexer::token_span& tokens) const override;
};

rule_parser::pointer empty();

}
#endif
