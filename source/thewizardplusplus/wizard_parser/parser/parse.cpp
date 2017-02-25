#include "parse.hpp"
#include "../utilities/positional_exception.hpp"
#include "../lexer/tokenize.hpp"
#include "../vendor/fmt/format.hpp"
#include <iterator>

using namespace thewizardplusplus::wizard_parser::lexer;
using namespace thewizardplusplus::wizard_parser::utilities;
using namespace fmt;

namespace thewizardplusplus {
namespace wizard_parser {
namespace parser {

ast_node parse(
	const rule_parser::pointer& rule,
	const token_group& tokens,
	const std::size_t code_length
) {
	const auto ast = rule->parse(std::cbegin(tokens), std::cend(tokens));
	if (!ast.node) {
		if (ast.last_token != std::cend(tokens)) {
			throw positional_exception{
				format("unexpected token {:s}", to_string(*ast.last_token)),
				ast.last_token->offset
			};
		} else {
			throw positional_exception{"the unexpected EOI", code_length};
		}
	}

	return *ast.node;
}

ast_node parse(
	const std::vector<lexeme>& lexemes,
	const std::unordered_set<std::string>& ignorable_tokens,
	const rule_parser::pointer& rule,
	std::string code
) {
	const auto tokens = tokenize(lexemes, ignorable_tokens, code);
	return parse(rule, tokens, code.size());
}

}
}
}
