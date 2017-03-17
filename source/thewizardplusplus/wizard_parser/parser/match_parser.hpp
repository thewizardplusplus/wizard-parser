#ifndef THEWIZARDPLUSPLUS_WIZARD_PARSER_PARSER_MATCH_PARSER_HEADER
#define THEWIZARDPLUSPLUS_WIZARD_PARSER_PARSER_MATCH_PARSER_HEADER

#include "rule_parser.hpp"
#include "match_type.hpp"
#include "../lexer/token.hpp"
#include "parsing_result.hpp"
#include "../vendor/gsl/span.hpp"
#include <string>
#include <cstddef>

namespace thewizardplusplus {
namespace wizard_parser {
namespace parser {

struct match_parser final: rule_parser {
	match_parser(const match_type match_kind, std::string sample);
	parsing_result parse(const gsl::span<lexer::token>& tokens) const override;

private:
	const match_type match_kind;
	const std::string sample;
};

namespace operators {

rule_parser::pointer operator""_t(const char* const sample, std::size_t);
rule_parser::pointer operator""_v(const char* const sample, std::size_t);

}
}
}
}
#endif
