#ifndef THEWIZARDPLUSPLUS_WIZARD_PARSER_PARSER_PARSE_HEADER
#define THEWIZARDPLUSPLUS_WIZARD_PARSER_PARSER_PARSE_HEADER

#include "rule_parser.hpp"
#include "../lexer/token_group.hpp"
#include "ast_node.hpp"
#include "../lexer/lexeme.hpp"
#include <cstddef>
#include <vector>
#include <string>
#include <unordered_set>

namespace thewizardplusplus {
namespace wizard_parser {
namespace parser {

ast_node parse(
	const rule_parser::pointer& rule,
	const lexer::token_group& tokens,
	const std::size_t code_length
);
ast_node parse(
	std::vector<lexer::lexeme> lexemes,
	std::unordered_set<std::string> ignorable_tokens,
	const rule_parser::pointer& rule,
	std::string code
);

}
}
}
#endif
