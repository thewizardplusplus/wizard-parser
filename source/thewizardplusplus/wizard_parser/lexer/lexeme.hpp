#ifndef THEWIZARDPLUSPLUS_WIZARD_PARSER_LEXER_LEXEME_HEADER
#define THEWIZARDPLUSPLUS_WIZARD_PARSER_LEXER_LEXEME_HEADER

#include <regex>
#include <string>
#include <string_view>
#include <vector>

namespace thewizardplusplus::wizard_parser::lexer {

struct lexeme {
	std::regex pattern;
	std::string type;
};

using lexeme_match = std::match_results<std::string_view::const_iterator>;

using lexeme_group = std::vector<lexeme>;

lexeme_match match_lexeme(
	const lexeme& some_lexeme,
	const std::string_view& code
);

}
#endif
