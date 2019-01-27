#include "match_parser.hpp"
#include "ast_node.hpp"
#include <utility>
#include <memory>

namespace thewizardplusplus::wizard_parser::parser {

match_parser::match_parser(const match_type match_kind, std::string sample):
	match_kind{match_kind},
	sample{std::move(sample)}
{}

parsing_result match_parser::parse(const lexer::token_span& tokens) const {
	if (tokens.empty()) {
		return {};
	}

	auto matched_value = std::string{};
	switch (match_kind) {
	case match_type::by_type:
		matched_value = tokens[0].type;
		break;
	case match_type::by_value:
		matched_value = tokens[0].value;
		break;
	}
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
