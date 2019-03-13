#include "common.hpp"
#include "../../source/thewizardplusplus/wizard_parser/parser/ast_node.hpp"

namespace tests::common {

using namespace thewizardplusplus::wizard_parser;

parser::parsing_result ast_from_token(
	const lexer::token_span& tokens,
	const std::size_t& index
) {
	const auto [type, value, offset] = tokens[index];
	return {parser::ast_node{type, value, {}, offset}, tokens.subspan(index + 1)};
}

parser::parsing_result ast_with_type(
	const parser::parsing_result& ast,
	const std::string& type
) {
	return {parser::ast_node{type, {}, {*ast.node}}, ast.rest_tokens};
}

}
