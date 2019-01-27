#ifndef THEWIZARDPLUSPLUS_WIZARD_PARSER_LEXER_TOKENIZE_HEADER
#define THEWIZARDPLUSPLUS_WIZARD_PARSER_LEXER_TOKENIZE_HEADER

#include "lexeme.hpp"
#include "token.hpp"
#include <string_view>

namespace thewizardplusplus::wizard_parser::lexer {

token_group tokenize(const lexeme_group& lexemes, const std::string_view& code);

}
#endif
