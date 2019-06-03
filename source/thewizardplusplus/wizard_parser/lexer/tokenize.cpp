#include "tokenize.hpp"
#include "../vendor/range/v3/view/concat.hpp"
#include "../vendor/range/v3/view/single.hpp"
#include "../vendor/range/v3/view/filter.hpp"
#include "../vendor/range/v3/to_container.hpp"
#include "../exceptions/unexpected_entity_exception.hpp"

namespace thewizardplusplus::wizard_parser::lexer {

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

tokenizing_result tokenize(
	const lexeme_group& lexemes,
	const exception_group& exceptions,
	const std::string_view& code,
	const std::size_t& offset
) {
	const auto [tokens, rest_offset] = tokenize(lexemes, code, offset);
	const auto filtered_tokens = tokens
		| ranges::view::filter([&] (const auto& token) {
			return !exceptions.count(token.type);
		})
		| ranges::to_<lexer::token_group>();
	return {filtered_tokens, rest_offset};
}

token_group tokenize_all(
	const lexeme_group& lexemes,
	const exception_group& exceptions,
	const std::string_view& code,
	const std::size_t& offset
) {
	const auto [tokens, rest_offset] = tokenize(lexemes, exceptions, code, offset);
	if (rest_offset != code.size()) {
		const auto type = exceptions::entity_type::symbol;
		throw exceptions::unexpected_entity_exception<type>{rest_offset};
	}

	return tokens;
}

}
