#include "parse.hpp"
#include "../vendor/range/v3/numeric/accumulate.hpp"

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

}
