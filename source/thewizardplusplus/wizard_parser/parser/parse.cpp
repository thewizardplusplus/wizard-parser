#include "parse.hpp"
#include "../vendor/range/v3/numeric/accumulate.hpp"
#include "../exceptions/unexpected_entity_exception.hpp"

namespace thewizardplusplus::wizard_parser::parser {

parsing_result parse(
	const rule_parser::pointer& parser,
	const lexer::token_span& tokens,
	const transformers::ast_node_handler_group& handlers
) {
	const auto ast = parser->parse(tokens);
	if (!ast.node) {
		return ast;
	}

	return {
		ranges::accumulate(handlers, *ast.node, transformers::transform),
		ast.rest_tokens
	};
}

ast_node parse_all(
	const rule_parser::pointer& parser,
	const lexer::token_span& tokens,
	const transformers::ast_node_handler_group& handlers
) {
	const auto ast = parse(parser, tokens, handlers);
	const auto offset = lexer::get_offset(ast.rest_tokens);
	if (!ast.rest_tokens.empty()) {
		const auto type = exceptions::entity_type::token;
		throw exceptions::unexpected_entity_exception<type>{offset};
	}
	if (!ast.node) {
		const auto type = exceptions::entity_type::eoi;
		throw exceptions::unexpected_entity_exception<type>{offset};
	}

	return *ast.node;
}

}
