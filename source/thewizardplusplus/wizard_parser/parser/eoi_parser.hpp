#ifndef THEWIZARDPLUSPLUS_WIZARD_PARSER_PARSER_EOI_PARSER_HEADER
#define THEWIZARDPLUSPLUS_WIZARD_PARSER_PARSER_EOI_PARSER_HEADER

#include "token_parser.hpp"
#include "../lexer/token.hpp"
#include "parsing_result.hpp"
#include "rule_parser.hpp"
#include "../vendor/gsl/span.hpp"

namespace thewizardplusplus {
namespace wizard_parser {
namespace parser {

struct eoi_parser final: token_parser {
protected:
	virtual parsing_result parse_token(
		const gsl::span<lexer::token>& tokens
	) const override final;
	virtual parsing_result parse_eoi() const override final;
};

rule_parser::pointer eoi();

}
}
}
#endif
