#include "empty_parser.hpp"
#include "ast_node.hpp"
#include <memory>

namespace thewizardplusplus::wizard_parser::parser {

parsing_result empty_parser::parse(const lexer::token_span& tokens) const {
	const auto type = (+ast_node_type::nothing)._to_string();
	return {ast_node{type, {}, {}}, tokens};
}

rule_parser::pointer empty() {
	return std::make_shared<empty_parser>();
}

}
