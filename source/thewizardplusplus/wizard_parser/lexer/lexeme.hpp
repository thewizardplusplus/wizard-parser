#ifndef LEXER_LEXEME_HEADER
#define LEXER_LEXEME_HEADER

#include <regex>
#include <string>

namespace lexer {

struct lexeme {
	std::regex pattern;
	std::string type;
};

}
#endif
