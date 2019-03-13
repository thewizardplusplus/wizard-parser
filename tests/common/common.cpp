#include "common.hpp"
#include "../../source/thewizardplusplus/wizard_parser/parser/ast_node.hpp"

namespace tests::common {

using namespace thewizardplusplus::wizard_parser;

parser::parsing_result ast_with_type(
	const parser::parsing_result& ast,
	const std::string& type
) {
	return {parser::ast_node{type, {}, {*ast.node}}, ast.rest_tokens};
}

}
