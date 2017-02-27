#include "hide_parser.hpp"
#include <utility>
#include <memory>

using namespace thewizardplusplus::wizard_parser::lexer;
using namespace gsl;

namespace thewizardplusplus {
namespace wizard_parser {
namespace parser {

hide_parser::hide_parser(rule_parser::pointer parser):
	parser{std::move(parser)}
{}

parsing_result hide_parser::parse(const span<token>& tokens) const {
	auto ast = parser->parse(tokens);
	if (!ast.node) {
		return ast;
	}

	return parsing_result{
		ast_node{"nothing", {}, {}},
		std::move(ast.rest_tokens)
	};
}

namespace operators {

rule_parser::pointer operator&(rule_parser::pointer parser) {
	return std::make_shared<hide_parser>(std::move(parser));
}

}
}
}
}
