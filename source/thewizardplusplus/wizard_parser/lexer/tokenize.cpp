#include "tokenize.hpp"
#include "../vendor/range/v3/view/transform.hpp"
#include "../vendor/range/v3/algorithm/find_if.hpp"
#include "../vendor/range/v3/begin_end.hpp"
#include "../vendor/range/v3/view/concat.hpp"
#include "../vendor/range/v3/view/single.hpp"
#include <optional>
#include <tuple>

namespace thewizardplusplus::wizard_parser::lexer {

std::optional<token> find_matched_token(
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

tokenizing_result tokenize(
	const lexeme_group& lexemes,
	const std::string_view& code,
	const std::size_t& offset
) {
	const auto some_token = find_matched_token(lexemes, code);
	if (!some_token) {
		return {{}, offset};
	}

	const auto first_token = token{some_token->type, some_token->value, offset};
	const auto [rest_tokens, rest_offset] = tokenize(
		lexemes,
		code.substr(some_token->value.size()),
		offset+some_token->value.size()
	);
	return {
		ranges::view::concat(ranges::view::single(first_token), rest_tokens),
		rest_offset
	};
}

}
