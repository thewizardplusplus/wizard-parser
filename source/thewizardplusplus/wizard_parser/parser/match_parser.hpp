#ifndef THEWIZARDPLUSPLUS_WIZARD_PARSER_PARSER_MATCH_PARSER_HEADER
#define THEWIZARDPLUSPLUS_WIZARD_PARSER_PARSER_MATCH_PARSER_HEADER

#include "rule_parser.hpp"
#include "../lexer/token.hpp"
#include <cstdint>
#include <string>
#include <cstddef>

namespace thewizardplusplus::wizard_parser::parser {

enum class match_type: std::uint8_t { by_type, by_value };

struct match_parser final: rule_parser {
	match_parser(const match_type& type, const std::string& sample);
	parsing_result parse(const lexer::token_span& tokens) const override;

private:
	const match_type type;
	const std::string sample;
};

namespace operators {

rule_parser::pointer operator""_t(const char* const sample, std::size_t);
rule_parser::pointer operator""_v(const char* const sample, std::size_t);

}

}
#endif
