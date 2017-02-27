#include "flag_assignable_parser.hpp"
#include <utility>

using namespace thewizardplusplus::wizard_parser::lexer;
using namespace gsl;

namespace thewizardplusplus {
namespace wizard_parser {
namespace parser {

flag_assignable_parser::flag_assignable_parser(const ast_node_flag flag):
	flag{flag}
{}

rule_parser::pointer flag_assignable_parser::operator=(
	rule_parser::pointer parser
) {
	this->parser = std::move(parser);
	return shared_from_this();
}

parsing_result flag_assignable_parser::parse(const span<token>& tokens) const {
	auto ast = parser->parse(tokens);
	if (!ast.node) {
		return ast;
	}

	ast.node->flags = ast.node->flags | flag;
	return ast;
}

}
}
}
