#ifndef THEWIZARDPLUSPLUS_WIZARD_PARSER_LEXER_TOKENIZE_HEADER
#define THEWIZARDPLUSPLUS_WIZARD_PARSER_LEXER_TOKENIZE_HEADER

#include "token.hpp"
#include "lexeme.hpp"
#include <cstddef>
#include <unordered_set>
#include <string>
#include <string_view>

namespace thewizardplusplus::wizard_parser::lexer {

struct tokenizing_result {
	token_group tokens;
	std::size_t rest_offset;
};

using type_group = std::unordered_set<std::string>;

tokenizing_result tokenize(
	const lexeme_group& lexemes,
	const std::string_view& code,
	const std::size_t& offset=0
);
tokenizing_result tokenize(
	const lexeme_group& lexemes,
	const type_group& exceptions,
	const std::string_view& code,
	const std::size_t& offset=0
);
token_group tokenize_all(
	const lexeme_group& lexemes,
	const type_group& exceptions,
	const std::string_view& code,
	const std::size_t& offset=0
);

}
#endif
