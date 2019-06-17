#ifndef THEWIZARDPLUSPLUS_WIZARD_PARSER_TRANSFORMERS_TRANSFORM_HEADER
#define THEWIZARDPLUSPLUS_WIZARD_PARSER_TRANSFORMERS_TRANSFORM_HEADER

#include "../parser/ast_node.hpp"
#include <functional>
#include <vector>

namespace thewizardplusplus::wizard_parser::transformers {

using ast_node_handler =
	std::function<parser::ast_node(const parser::ast_node&)>;

using ast_node_handler_group = std::vector<ast_node_handler>;

extern const ast_node_handler_group default_ast_node_handlers;

parser::ast_node transform(
	const parser::ast_node& ast,
	const ast_node_handler& handler
);
parser::ast_node transform(
	const parser::ast_node& ast,
	const ast_node_handler_group& handlers = default_ast_node_handlers
);

}
#endif
