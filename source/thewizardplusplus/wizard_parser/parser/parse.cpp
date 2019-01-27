#include "parse.hpp"
#include "../utilities/positional_exception.hpp"
#include "../lexer/tokenize.hpp"
#include "../vendor/fmt/format.hpp"
#include <iterator>

using namespace thewizardplusplus::wizard_parser::lexer;
using namespace thewizardplusplus::wizard_parser::utilities;
using namespace gsl;
using namespace fmt;

namespace thewizardplusplus::wizard_parser::parser {

ast_node parse(
	const rule_parser::pointer& rule,
	const span<token>& tokens,
	const std::size_t code_length
) {
	const auto ast = rule->parse(tokens);
	if (!ast.node) {
		if (!ast.rest_tokens.empty()) {
			throw positional_exception{
				format("unexpected token {:s}", to_string(ast.rest_tokens[0])),
				ast.rest_tokens[0].offset
			};
		} else {
			throw positional_exception{"the unexpected EOI", code_length};
		}
	}

	return *ast.node;
}

ast_node parse(
	const lexeme_group& lexemes,
	const std::unordered_set<std::string>& ignorable_tokens,
	const rule_parser::pointer& rule,
	std::string code
) {
	auto tokens = tokenize(lexemes, ignorable_tokens, code);
	return parse(rule, tokens, code.size());
}

}
