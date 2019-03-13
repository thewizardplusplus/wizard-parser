#include "lexeme.hpp"
#include <iterator>

namespace thewizardplusplus::wizard_parser::lexer {

lexeme_match match_lexeme(
	const lexeme& some_lexeme,
	const std::string_view& code
) {
	auto match = lexeme_match{};
	std::regex_search(
		std::cbegin(code),
		std::cend(code),
		match,
		some_lexeme.pattern,
		std::regex_constants::match_continuous
	);

	return match;
}

}
