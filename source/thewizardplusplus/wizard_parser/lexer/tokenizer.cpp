#include "tokenizer.hpp"
#include "../utilities/positional_exception.hpp"
#include "../vendor/json.hpp"
#include <iterator>

using namespace thewizardplusplus::wizard_parser::utilities;
using namespace nlohmann;

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
	start{std::cbegin(this->code)}
{}

token_group tokenizer::tokenize() {
	auto tokens = token_group{};
	while (start != std::cend(code)) {
		auto matched_token = find_longest_matched_token();
		if (!matched_token.second) {
			throw positional_exception{
				"invalid symbol " + json(std::string{*start}).dump(),
				get_current_symbol_offset()
			};
		}

		std::advance(start, matched_token.first.value.size());
		if (ignorable_tokens.count(matched_token.first.type) == 0) {
			tokens.push_back(std::move(matched_token.first));
		}
	}

	return tokens;
}

std::pair<token, bool> tokenizer::find_longest_matched_token() const {
	auto matched_token = std::pair<token, bool>{};
	for (const auto& some_lexeme: lexemes) {
		const auto match = match_lexeme(some_lexeme);
		if (
			!match.second
			|| static_cast<std::size_t>(match.first.length())
				<= matched_token.first.value.size()
		) {
			continue;
		}

		matched_token = {
			{some_lexeme.type, match.first.str(), get_current_symbol_offset()},
			true
		};
	}

	return matched_token;
}

std::pair<std::smatch, bool> tokenizer::match_lexeme(
	const lexeme& some_lexeme
) const {
	auto match = std::pair<std::smatch, bool>{};
	match.second = std::regex_search(
		start,
		std::cend(code),
		match.first,
		some_lexeme.pattern,
		std::regex_constants::match_continuous
	);

	return match;
}

std::size_t tokenizer::get_current_symbol_offset() const {
	return static_cast<std::size_t>(std::distance(std::begin(code), start));
}

}
}
}
