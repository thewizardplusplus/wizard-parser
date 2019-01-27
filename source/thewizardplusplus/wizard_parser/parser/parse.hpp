#ifndef THEWIZARDPLUSPLUS_WIZARD_PARSER_PARSER_PARSE_HEADER
#define THEWIZARDPLUSPLUS_WIZARD_PARSER_PARSER_PARSE_HEADER

#include "rule_parser.hpp"
#include "../lexer/token.hpp"
#include "ast_node.hpp"
#include "../lexer/lexeme.hpp"
#include "../vendor/gsl/span.hpp"
#include <cstddef>
#include <vector>
#include <string>
#include <unordered_set>

namespace thewizardplusplus::wizard_parser::parser {

ast_node parse(
	const rule_parser::pointer& rule,
	const gsl::span<lexer::token>& tokens,
	const std::size_t code_length
);
ast_node parse(
	const lexer::lexeme_group& lexemes,
	const std::unordered_set<std::string>& ignorable_tokens,
	const rule_parser::pointer& rule,
	std::string code
);

}
#endif
