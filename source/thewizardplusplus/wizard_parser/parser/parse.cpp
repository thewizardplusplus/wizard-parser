#include "parse.hpp"
#include "../exceptions/unexpected_entity_exception.hpp"

namespace thewizardplusplus::wizard_parser::parser {

ast_node parse(
	const rule_parser::pointer& rule,
	const lexer::token_span& tokens
) {
	const auto ast = rule->parse(tokens);
	if (!ast.node) {
		using namespace exceptions;

		const auto offset = lexer::get_offset(ast.rest_tokens);
		if (!ast.rest_tokens.empty()) {
			throw unexpected_entity_exception<entity_type::token>{offset};
		} else {
			throw unexpected_entity_exception<entity_type::eoi>{offset};
		}
	}

	return *ast.node;
}

}
