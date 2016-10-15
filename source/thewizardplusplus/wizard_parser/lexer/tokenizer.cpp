#include "tokenizer.hpp"
#include "../utilities/string_utilities.hpp"
#include "../utilities/set_utilities.hpp"
#include <sstream>
#include <ios>
#include <iomanip>
#include <cstdint>
#include <cctype>
#include <stdexcept>
#include <iterator>
#include <cstddef>

using namespace utilities;

namespace {

std::string to_hex(const char symbol) {
	auto out = std::ostringstream{};
	out << std::showbase << std::hex
		<< std::setw(4) << std::setfill('0') << std::internal
		// http://stackoverflow.com/a/5042335
		<< static_cast<std::uint64_t>(
				reinterpret_cast<const std::uint8_t&>(symbol)
			);

	return out.str();
}

[[noreturn]] void process_invalid_symbol(const char invalid_symbol) {
	const auto symbol_view = std::isprint(invalid_symbol)
		? quote(std::string{1, invalid_symbol})
		: to_hex(invalid_symbol);
	throw std::runtime_error{"the invalid symbol " + symbol_view};
}

}

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
			process_invalid_symbol(*start);
		}

		std::advance(start, matched_token.first.value.size());
		if (contains(ignorable_tokens, matched_token.first.type)) {
			continue;
		}

		tokens.push_back(std::move(matched_token.first));
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
			{
				some_lexeme.type,
				match.first.str(),
				static_cast<std::size_t>(std::distance(std::begin(code), start))
			},
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

}
