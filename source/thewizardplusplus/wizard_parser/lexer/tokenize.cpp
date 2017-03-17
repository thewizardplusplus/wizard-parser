#include "tokenize.hpp"
#include "../utilities/positional_exception.hpp"
#include "../vendor/optional.hpp"
#include "../vendor/json.hpp"
#include "../vendor/fmt/format.hpp"
#include <regex>
#include <cstddef>
#include <utility>

using namespace thewizardplusplus::wizard_parser::lexer;
using namespace thewizardplusplus::wizard_parser::utilities;
using namespace gsl;
using namespace std::experimental;
using namespace nlohmann;
using namespace fmt;

namespace {

std::match_results<string_span<>::const_iterator> match_lexeme(
	const lexeme& some_lexeme,
	const string_span<>& code
) {
	auto match = std::match_results<string_span<>::const_iterator>{};
	std::regex_search(
		// std::cbegin() returns not constant iterator for gsl::string_span
		code.cbegin(),
		// std::cend() returns not constant iterator for gsl::string_span
		code.cend(),
		match,
		some_lexeme.pattern,
		std::regex_constants::match_continuous
	);

	return match;
}

optional<token> find_longest_matched_token(
	const std::vector<lexeme>& lexemes,
	const string_span<>& code,
	const std::size_t offset
) {
	auto matched_token = optional<token>{};
	for (const auto& some_lexeme: lexemes) {
		const auto match = match_lexeme(some_lexeme, code);
		if (
			!match.empty()
			&& (!matched_token
			|| matched_token->value.size()
				< static_cast<std::size_t>(match.length()))
		) {
			matched_token = token{some_lexeme.type, match.str(), offset};
		}
	}

	return matched_token;
}

}

namespace thewizardplusplus {
namespace wizard_parser {
namespace lexer {

token_group tokenize(
	const std::vector<lexeme>& lexemes,
	const std::unordered_set<std::string>& ignorable_tokens,
	const string_span<>& code
) {
	auto tokens = token_group{};
	auto rest_code = code;
	auto offset = std::size_t{};
	while (!rest_code.empty()) {
		auto matched_token = find_longest_matched_token(
			lexemes,
			rest_code,
			offset
		);
		if (!matched_token) {
			throw positional_exception{
				format(
					"invalid symbol {:s}",
					json(std::string{rest_code[0]}).dump()
				),
				offset
			};
		}

		rest_code = rest_code.subspan(
			static_cast<string_span<>::index_type>(matched_token->value.size())
		);
		offset += matched_token->value.size();

		if (ignorable_tokens.count(matched_token->type) == 0) {
			tokens.push_back(std::move(*matched_token));
		}
	}

	return tokens;
}

}
}
}