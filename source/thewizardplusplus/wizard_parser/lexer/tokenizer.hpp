#ifndef LEXER_TOKENIZER_HEADER
#define LEXER_TOKENIZER_HEADER

#include "lexeme.hpp"
#include "token_group.hpp"
#include "token.hpp"
#include <vector>
#include <string>
#include <unordered_set>
#include <utility>
#include <regex>

namespace lexer {

struct tokenizer {
	tokenizer(
		std::vector<lexeme> lexemes,
		std::unordered_set<std::string> ignorable_tokens,
		std::string code
	);
	token_group tokenize();

private:
	const std::vector<lexeme> lexemes;
	const std::unordered_set<std::string> ignorable_tokens;
	const std::string code;
	std::string::const_iterator start;

	std::pair<token, bool> find_longest_matched_token() const;
	std::pair<std::smatch, bool> match_lexeme(const lexeme& some_lexeme) const;
};

}
#endif
