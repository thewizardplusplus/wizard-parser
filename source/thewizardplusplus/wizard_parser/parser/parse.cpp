#include "parse.hpp"
#include "../utilities/unexpected_token_exception.hpp"
#include "../utilities/unexpected_eoi_exception.hpp"
#include "../lexer/tokenize.hpp"
#include <iterator>
#include <limits>

using namespace thewizardplusplus::wizard_parser::lexer;
using namespace thewizardplusplus::wizard_parser::utilities;

namespace thewizardplusplus::wizard_parser::parser {

ast_node parse(
	const rule_parser::pointer& rule,
	const lexer::token_span& tokens
) {
	const auto ast = rule->parse(tokens);
	if (!ast.node) {
		if (!ast.rest_tokens.empty()) {
			throw unexpected_token_exception{ast.rest_tokens[0].offset};
		} else {
			throw unexpected_eoi_exception{std::numeric_limits<std::size_t>::max()};
		}
	}

	return *ast.node;
}

ast_node parse(
	const lexeme_group& lexemes,
	const rule_parser::pointer& rule,
	std::string code
) {
	auto tokens = tokenize(lexemes, code);
	return parse(rule, tokens);
}

}
