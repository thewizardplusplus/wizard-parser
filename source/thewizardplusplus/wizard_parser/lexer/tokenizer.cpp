#include "tokenizer.hpp"
#include "../utilities/positional_exception.hpp"
#include "../vendor/json.hpp"
#include "../vendor/fmt/format.hpp"
#include <iterator>

using namespace thewizardplusplus::wizard_parser::utilities;
using namespace nlohmann;
using namespace fmt;
using namespace gsl;
using namespace std::experimental;

namespace thewizardplusplus {
namespace wizard_parser {
namespace lexer {

tokenizer::tokenizer(
	std::vector<lexeme> lexemes,
	std::unordered_set<std::string> ignorable_tokens,
	std::string code
):
	lexemes{std::move(lexemes)},
	ignorable_tokens{std::move(ignorable_tokens)},
	code{std::move(code)},
	rest_code{this->code}
{}

token_group tokenizer::tokenize() {
	auto tokens = token_group{};
	while (!rest_code.empty()) {
		auto matched_token = find_longest_matched_token();
		if (!matched_token) {
			throw positional_exception{
				format(
					"invalid symbol {:s}",
					json(std::string{rest_code[0]}).dump()
				),
				get_current_symbol_offset()
			};
		}

		rest_code = rest_code.subspan(
			static_cast<string_span<>::index_type>(matched_token->value.size())
		);
		if (ignorable_tokens.count(matched_token->type) == 0) {
			tokens.push_back(std::move(*matched_token));
		}
	}

	return tokens;
}

optional<token> tokenizer::find_longest_matched_token() const {
	auto matched_token = optional<token>{};
	for (const auto& some_lexeme: lexemes) {
		const auto match = match_lexeme(some_lexeme);
		if (
			!match.empty()
			&& (!matched_token
			|| matched_token->value.size()
				< static_cast<std::size_t>(match.length()))
		) {
			matched_token = token{
				some_lexeme.type,
				match.str(),
				get_current_symbol_offset()
			};
		}
	}

	return matched_token;
}

std::match_results<string_span<>::const_iterator> tokenizer::match_lexeme(
	const lexeme& some_lexeme
) const {
	auto match = std::match_results<string_span<>::const_iterator>{};
	std::regex_search(
		// std::cbegin() returns not constant iterator for gsl::string_span
		rest_code.cbegin(),
		// std::cend() returns not constant iterator for gsl::string_span
		rest_code.cend(),
		match,
		some_lexeme.pattern,
		std::regex_constants::match_continuous
	);

	return match;
}

std::size_t tokenizer::get_current_symbol_offset() const {
	return static_cast<std::size_t>(rest_code.data() - code.data());
}

}
}
}
