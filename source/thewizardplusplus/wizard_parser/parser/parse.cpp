#include "parse.hpp"
#include <iterator>
#include <sstream>
#include <stdexcept>

using namespace thewizardplusplus::wizard_parser::lexer;

namespace thewizardplusplus {
namespace wizard_parser {
namespace parser {

ast_node parse(const rule_parser::pointer& rule, const token_group& tokens) {
	const auto ast = rule->parse(std::cbegin(tokens), std::cend(tokens));
	if (!ast.is_parsed) {
		if (ast.last_token != std::cend(tokens)) {
			auto out = std::ostringstream{};
			out << *ast.last_token;

			throw std::runtime_error{"the unexpected token " + out.str()};
		} else {
			throw std::runtime_error{"the unexpected EOI"};
		}
	}

	return ast.node;
}

}
}
}
