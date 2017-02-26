#ifndef THEWIZARDPLUSPLUS_WIZARD_PARSER_PARSER_VALUE_MATCH_PARSER_HEADER
#define THEWIZARDPLUSPLUS_WIZARD_PARSER_PARSER_VALUE_MATCH_PARSER_HEADER

#include "rule_parser.hpp"
#include "../lexer/token.hpp"
#include "parsing_result.hpp"
#include "../vendor/gsl/span.hpp"
#include <string>
#include <cstddef>

namespace thewizardplusplus {
namespace wizard_parser {
namespace parser {

struct value_match_parser final: rule_parser {
	explicit value_match_parser(std::string sample);
	parsing_result parse(const gsl::span<lexer::token>& tokens) const override;

private:
	const std::string sample;
};

namespace operators {

rule_parser::pointer operator""_v(const char* const sample, std::size_t);

}
}
}
}
#endif
