#include "parse.hpp"
#include "../utilities/unexpected_token_exception.hpp"
#include "../utilities/unexpected_eoi_exception.hpp"
#include <limits>

namespace thewizardplusplus::wizard_parser::parser {

ast_node parse(
	const rule_parser::pointer& rule,
	const lexer::token_span& tokens
) {
	const auto ast = rule->parse(tokens);
	if (!ast.node) {
		if (!ast.rest_tokens.empty()) {
			throw utilities::unexpected_token_exception{ast.rest_tokens[0].offset};
		} else {
			throw utilities::unexpected_eoi_exception{
				std::numeric_limits<std::size_t>::max()
			};
		}
	}

	return *ast.node;
}

}
