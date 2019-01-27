#include "parse.hpp"
#include "../utilities/unexpected_token_exception.hpp"
#include "../lexer/tokenize.hpp"
#include <iterator>

using namespace thewizardplusplus::wizard_parser::lexer;
using namespace thewizardplusplus::wizard_parser::utilities;

namespace thewizardplusplus::wizard_parser::parser {

ast_node parse(
	const rule_parser::pointer& rule,
	const lexer::token_span& tokens,
	const std::size_t code_length
) {
	const auto ast = rule->parse(tokens);
	if (!ast.node) {
		if (!ast.rest_tokens.empty()) {
			throw unexpected_token_exception{ast.rest_tokens[0].offset};
		} else {
			throw positional_exception{"the unexpected EOI", code_length};
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
	return parse(rule, tokens, code.size());
}

}
