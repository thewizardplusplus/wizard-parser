#include "tokenize.hpp"
#include "../utilities/positional_exception.hpp"
#include "../vendor/json.hpp"
#include "../vendor/fmt/format.hpp"
#include <regex>
#include <iterator>
#include <optional>
#include <vector>
#include <tuple>
#include <algorithm>
#include <cstddef>
#include <string>

using namespace thewizardplusplus::wizard_parser::utilities;
using namespace nlohmann;
using namespace fmt;

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
	const std::string_view& code
) {
	auto tokens = token_group{};
	auto rest_code = code;
	auto offset = std::size_t{};
	while (!rest_code.empty()) {
		const auto matched_token = find_matched_token(lexemes, rest_code);
		if (!matched_token) {
			throw positional_exception{
				format(
					"invalid symbol {:s}",
					json(std::string{rest_code[0]}).dump()
				),
				offset
			};
		}

		tokens.push_back({matched_token->type, matched_token->value, offset});
		rest_code = rest_code.substr(matched_token->value.size());
		offset += matched_token->value.size();
	}

	return tokens;
}

}
