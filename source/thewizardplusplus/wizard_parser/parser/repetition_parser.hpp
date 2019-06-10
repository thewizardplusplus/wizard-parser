#ifndef THEWIZARDPLUSPLUS_WIZARD_PARSER_PARSER_REPETITION_PARSER_HEADER
#define THEWIZARDPLUSPLUS_WIZARD_PARSER_PARSER_REPETITION_PARSER_HEADER

#include "rule_parser.hpp"
#include "../utilities/utilities.hpp"
#include "../lexer/token.hpp"
#include <cstddef>
#include <tuple>

namespace thewizardplusplus::wizard_parser::parser {

struct repetition_parser final: rule_parser {
	repetition_parser(
		const rule_parser::pointer& parser,
		const std::size_t& minimal_number=0,
		const std::size_t& maximal_number=utilities::integral_infinity
	);
	parsing_result parse(const lexer::token_span& tokens) const override;

private:
	using counted_result = std::tuple<parsing_result, std::size_t>;

	const rule_parser::pointer parser;
	const std::size_t minimal_number;
	const std::size_t maximal_number;

	counted_result parse_and_count(
		const lexer::token_span& tokens,
		const std::size_t& counter=0
	) const;
};

namespace operators {

rule_parser::pointer operator-(const rule_parser::pointer& parser);
rule_parser::pointer operator*(const rule_parser::pointer& parser);
rule_parser::pointer operator+(const rule_parser::pointer& parser);

}

}
#endif
