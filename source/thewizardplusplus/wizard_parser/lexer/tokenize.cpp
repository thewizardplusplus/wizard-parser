#include "tokenize.hpp"
#include "../exceptions/unexpected_entity_exception.hpp"
#include <regex>
#include <iterator>
#include <optional>
#include <vector>
#include <tuple>
#include <algorithm>

namespace thewizardplusplus::wizard_parser::lexer {

using match_t = std::match_results<std::string_view::const_iterator>;

match_t match_lexeme(const lexeme& some_lexeme, const std::string_view& code) {
	auto match = match_t{};
	std::regex_search(
		std::cbegin(code),
		std::cend(code),
		match,
		some_lexeme.pattern,
		std::regex_constants::match_continuous
	);

	return match;
}

std::optional<token> find_matched_token(
	const lexeme_group& lexemes,
	const std::string_view& code
) {
	auto matches = std::vector<std::tuple<lexeme, match_t>>{};
	std::transform(
		std::cbegin(lexemes),
		std::cend(lexemes),
		std::back_inserter(matches),
		[&] (const auto& lexeme) {
			const auto match = match_lexeme(lexeme, code);
			return std::make_tuple(lexeme, match);
		}
	);

	const auto match = std::find_if(
		std::cbegin(matches),
		std::cend(matches),
		[] (const auto& match) { return !std::get<match_t>(match).empty(); }
	);
	if (match == std::cend(matches)) {
		return std::nullopt;
	}

	return token{std::get<lexeme>(*match).type, std::get<match_t>(*match).str()};
}

token_group tokenize(
	const lexeme_group& lexemes,
	const std::string_view& code,
	const std::size_t& offset
) {
	if (code.empty()) {
		return {};
	}

	const auto some_token = find_matched_token(lexemes, code);
	if (!some_token) {
		using namespace exceptions;
		throw unexpected_entity_exception<entity_type::symbol>{offset};
	}

	auto tokens = token_group{{some_token->type, some_token->value, offset}};
	const auto rest_tokens = tokenize(
		lexemes,
		code.substr(some_token->value.size()),
		offset+some_token->value.size()
	);
	std::copy(
		std::cbegin(rest_tokens),
		std::cend(rest_tokens),
		std::back_inserter(tokens)
	);

	return tokens;
}

}
