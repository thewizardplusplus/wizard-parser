#ifndef THEWIZARDPLUSPLUS_WIZARD_PARSER_LEXER_TOKENIZE_HEADER
#define THEWIZARDPLUSPLUS_WIZARD_PARSER_LEXER_TOKENIZE_HEADER

#include "lexeme.hpp"
#include "token_group.hpp"
#include "../vendor/gsl/string_span.hpp"
#include <vector>
#include <string>
#include <unordered_set>

namespace thewizardplusplus {
namespace wizard_parser {
namespace lexer {

token_group tokenize(
	const std::vector<lexeme>& lexemes,
	const std::unordered_set<std::string>& ignorable_tokens,
	const gsl::string_span<>& code
);

}
}
}
#endif
