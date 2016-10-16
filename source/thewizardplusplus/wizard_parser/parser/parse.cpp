#include "parse.hpp"
#include "../utilities/positional_exception.hpp"
#include "../lexer/tokenizer.hpp"
#include <iterator>
#include <sstream>
#include <stdexcept>
#include <utility>

using namespace thewizardplusplus::wizard_parser::lexer;
using namespace thewizardplusplus::wizard_parser::utilities;

namespace thewizardplusplus {
namespace wizard_parser {
namespace parser {

ast_node parse(
	const rule_parser::pointer& rule,
	const token_group& tokens,
	const std::size_t code_length
) {
	const auto ast = rule->parse(std::cbegin(tokens), std::cend(tokens));
	if (!ast.is_parsed) {
		if (ast.last_token != std::cend(tokens)) {
			auto out = std::ostringstream{};
			out << *ast.last_token;

			throw positional_exception{
				"unexpected token " + out.str(),
				ast.last_token->offset
			};
		} else {
			throw positional_exception{"the unexpected EOI", code_length};
		}
	}

	return ast.node;
}

ast_node parse(
	std::vector<lexeme> lexemes,
	std::unordered_set<std::string> ignorable_tokens,
	const rule_parser::pointer& rule,
	std::string code
) {
	const auto code_length = code.size();
	const auto tokens = tokenizer{
			std::move(lexemes),
			std::move(ignorable_tokens),
			std::move(code)
		}
		.tokenize();
	return parse(rule, tokens, code_length);
}

}
}
}
