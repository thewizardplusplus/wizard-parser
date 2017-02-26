#ifndef THEWIZARDPLUSPLUS_WIZARD_PARSER_PARSER_EOI_PARSER_HEADER
#define THEWIZARDPLUSPLUS_WIZARD_PARSER_PARSER_EOI_PARSER_HEADER

#include "rule_parser.hpp"
#include "../lexer/token.hpp"
#include "parsing_result.hpp"
#include "../vendor/gsl/span.hpp"

namespace thewizardplusplus {
namespace wizard_parser {
namespace parser {

struct eoi_parser final: rule_parser {
	parsing_result parse(const gsl::span<lexer::token>& tokens) const override;
};

rule_parser::pointer eoi();

}
}
}
#endif
