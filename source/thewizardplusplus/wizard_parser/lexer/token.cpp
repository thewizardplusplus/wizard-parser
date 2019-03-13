#include "token.hpp"
#include "../utilities/utilities.hpp"
#include "../vendor/range/v3/view/transform.hpp"
#include "../vendor/range/v3/algorithm/find_if.hpp"
#include "../vendor/range/v3/begin_end.hpp"

namespace thewizardplusplus::wizard_parser::lexer {

bool operator==(const token& token_1, const token& token_2) {
	return to_tuple(token_1) == to_tuple(token_2);
}

std::ostream& operator<<(std::ostream& stream, const token& some_token) {
	stream << nlohmann::json(some_token);
	return stream;
}

token_tuple to_tuple(const token& some_token) {
	return std::make_tuple(some_token.type, some_token.value, some_token.offset);
}

void to_json(nlohmann::json& json, const token& some_token) {
	json = {
		{"type", some_token.type},
		{"value", some_token.value},
		{"offset", some_token.offset}
	};
}

std::size_t get_offset(const token_span& tokens) {
	return !tokens.empty() ? tokens[0].offset : utilities::integral_infinity;
}

token_optional find_matched_token(
	const lexeme_group& lexemes,
	const std::string_view& code
) {
	const auto matches = lexemes
		| ranges::view::transform([&] (const auto& lexeme) {
			const auto match = match_lexeme(lexeme, code);
			return std::make_tuple(lexeme, match);
		});
	const auto match = ranges::find_if(matches, [] (const auto& match) {
		return !std::get<lexeme_match>(match).empty();
	});
	return match != ranges::cend(matches)
		? std::make_optional(token{
			std::get<lexeme>(*match).type,
			std::get<lexeme_match>(*match).str()
		})
		: std::nullopt;
}

}
