#ifndef THEWIZARDPLUSPLUS_WIZARD_PARSER_PARSER_EOI_PARSER_HEADER
#define THEWIZARDPLUSPLUS_WIZARD_PARSER_PARSER_EOI_PARSER_HEADER

#include "rule_parser.hpp"
#include "../lexer/token.hpp"

namespace thewizardplusplus::wizard_parser::parser {

struct eoi_parser final: rule_parser {
	parsing_result parse(const lexer::token_span& tokens) const override;
};

rule_parser::pointer eoi();

}
#endif
