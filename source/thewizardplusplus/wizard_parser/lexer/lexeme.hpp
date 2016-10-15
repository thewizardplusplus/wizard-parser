#ifndef THEWIZARDPLUSPLUS_WIZARD_PARSER_LEXER_LEXEME_HEADER
#define THEWIZARDPLUSPLUS_WIZARD_PARSER_LEXER_LEXEME_HEADER

#include <regex>
#include <string>

namespace thewizardplusplus {
namespace wizard_parser {
namespace lexer {

struct lexeme {
	std::regex pattern;
	std::string type;
};

}
}
}
#endif
