#include "parse.hpp"
#include "../utilities/unexpected_entity_exception.hpp"
#include "common.hpp"

namespace thewizardplusplus::wizard_parser::parser {

ast_node parse(
	const rule_parser::pointer& rule,
	const lexer::token_span& tokens
) {
	const auto ast = rule->parse(tokens);
	if (!ast.node) {
		using namespace utilities;

		if (!ast.rest_tokens.empty()) {
			throw unexpected_entity_exception<entity_type::token>{
				ast.rest_tokens[0].offset
			};
		} else {
			throw unexpected_entity_exception<entity_type::eoi>{integral_infinity};
		}
	}

	return *ast.node;
}

}
