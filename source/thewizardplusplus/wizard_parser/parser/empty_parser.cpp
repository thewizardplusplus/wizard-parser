#include "empty_parser.hpp"
#include "ast_node.hpp"
#include <memory>

namespace thewizardplusplus::wizard_parser::parser {

parsing_result empty_parser::parse(const lexer::token_span& tokens) const {
	return {ast_node{"nothing", {}, {}}, tokens};
}

rule_parser::pointer empty() {
	return std::make_shared<empty_parser>();
}

}
