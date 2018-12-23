#ifndef THEWIZARDPLUSPLUS_WIZARD_PARSER_LEXER_LEXEME_HEADER
#define THEWIZARDPLUSPLUS_WIZARD_PARSER_LEXER_LEXEME_HEADER

#include <regex>
#include <string>

namespace thewizardplusplus::wizard_parser::lexer {

struct lexeme {
	std::regex pattern;
	std::string type;
};

}
#endif
