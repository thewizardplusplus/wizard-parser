#include "eoi_parser.hpp"
#include "ast_node.hpp"
#include <memory>

namespace thewizardplusplus::wizard_parser::parser {

parsing_result eoi_parser::parse(const lexer::token_span& tokens) const {
	const auto type = (+ast_node_type::eoi)._to_string();
	return tokens.empty()
		? parsing_result{ast_node{type, {}, {}, lexer::get_offset(tokens)}, {}}
		: parsing_result{{}, tokens};
}

rule_parser::pointer eoi() {
	return std::make_shared<eoi_parser>();
}

}
