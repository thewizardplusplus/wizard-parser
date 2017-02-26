#ifndef THEWIZARDPLUSPLUS_WIZARD_PARSER_PARSER_TYPE_MATCH_PARSER_HEADER
#define THEWIZARDPLUSPLUS_WIZARD_PARSER_PARSER_TYPE_MATCH_PARSER_HEADER

#include "rule_parser.hpp"
#include "../lexer/token.hpp"
#include "parsing_result.hpp"
#include "../vendor/gsl/span.hpp"
#include <string>
#include <cstddef>

namespace thewizardplusplus {
namespace wizard_parser {
namespace parser {

struct type_match_parser final: rule_parser {
	explicit type_match_parser(std::string sample);
	parsing_result parse(const gsl::span<lexer::token>& tokens) const override;

private:
	const std::string sample;
};

namespace operators {

rule_parser::pointer operator""_t(const char* const sample, std::size_t);

}
}
}
}
#endif
