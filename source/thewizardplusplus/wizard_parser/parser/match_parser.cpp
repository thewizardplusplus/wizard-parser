#include "match_parser.hpp"
#include "ast_node.hpp"
#include <memory>

namespace thewizardplusplus::wizard_parser::parser {

match_parser::match_parser(const match_type& type, const std::string& sample):
	type{type},
	sample{sample}
{}

parsing_result match_parser::parse(const lexer::token_span& tokens) const {
	if (tokens.empty()) {
		return {{}, {}};
	}

	const auto token = tokens[0];
	const auto match = type == match_type::by_type ? token.type : token.value;
	return match == sample
		? parsing_result{
			ast_node{token.type, token.value, {}, lexer::get_offset(tokens)},
			tokens.subspan(1)
		}
		: parsing_result{{}, tokens};
}

namespace operators {

rule_parser::pointer operator""_t(const char* const sample, std::size_t) {
	return std::make_shared<match_parser>(match_type::by_type, sample);
}

rule_parser::pointer operator""_v(const char* const sample, std::size_t) {
	return std::make_shared<match_parser>(match_type::by_value, sample);
}

}

}
