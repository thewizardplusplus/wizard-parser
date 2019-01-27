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
		return {};
	}

	const auto matched_value =
		type == match_type::by_type ? tokens[0].type : tokens[0].value;
	if (matched_value != sample) {
		return {{}, tokens};
	}

	return {ast_node{tokens[0].type, tokens[0].value, {}}, tokens.subspan(1)};
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
