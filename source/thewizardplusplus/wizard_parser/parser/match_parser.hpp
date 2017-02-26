#ifndef THEWIZARDPLUSPLUS_WIZARD_PARSER_PARSER_MATCH_PARSER_HEADER
#define THEWIZARDPLUSPLUS_WIZARD_PARSER_PARSER_MATCH_PARSER_HEADER

#include "token_parser.hpp"
#include "../lexer/token.hpp"
#include "parsing_result.hpp"
#include "../vendor/gsl/span.hpp"
#include <string>

namespace thewizardplusplus {
namespace wizard_parser {
namespace parser {

struct match_parser: token_parser {
	explicit match_parser(std::string sample);

protected:
	const std::string sample;

	virtual parsing_result parse_token(
		const gsl::span<lexer::token>& tokens
	) const override final;
	virtual parsing_result parse_eoi() const override final;
	virtual bool is_match(const lexer::token& token) const = 0;
};

}
}
}
#endif
