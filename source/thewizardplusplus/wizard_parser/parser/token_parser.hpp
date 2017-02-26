#ifndef THEWIZARDPLUSPLUS_WIZARD_PARSER_PARSER_TOKEN_PARSER_HEADER
#define THEWIZARDPLUSPLUS_WIZARD_PARSER_PARSER_TOKEN_PARSER_HEADER

#include "rule_parser.hpp"
#include "../lexer/token.hpp"
#include "parsing_result.hpp"
#include "../vendor/gsl/span.hpp"

namespace thewizardplusplus {
namespace wizard_parser {
namespace parser {

struct token_parser: rule_parser {
	virtual parsing_result parse(
		const gsl::span<lexer::token>& tokens
	) const override final;

protected:
	virtual parsing_result parse_token(
		const gsl::span<lexer::token>& tokens
	) const = 0;
	virtual parsing_result parse_eoi() const = 0;
};

}
}
}
#endif
