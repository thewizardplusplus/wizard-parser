#ifndef THEWIZARDPLUSPLUS_WIZARD_PARSER_TRANSFORMERS_TRANSFORM_HEADER
#define THEWIZARDPLUSPLUS_WIZARD_PARSER_TRANSFORMERS_TRANSFORM_HEADER

#include "../parser/ast_node.hpp"
#include <functional>

namespace thewizardplusplus::wizard_parser::transformers {

using ast_node_handler =
	std::function<parser::ast_node(const parser::ast_node&)>;

parser::ast_node transform(
	const parser::ast_node& ast,
	const ast_node_handler& handler
);

}
#endif
