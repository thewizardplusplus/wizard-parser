#ifndef THEWIZARDPLUSPLUS_WIZARD_PARSER_PARSER_FLAG_ASSIGNABLE_PARSER_HEADER
#define THEWIZARDPLUSPLUS_WIZARD_PARSER_PARSER_FLAG_ASSIGNABLE_PARSER_HEADER

#include "rule_parser.hpp"
#include "ast_node_flag.hpp"
#include "../lexer/token.hpp"
#include "parsing_result.hpp"
#include "../vendor/gsl/span.hpp"
#include <memory>

namespace thewizardplusplus {
namespace wizard_parser {
namespace parser {

struct flag_assignable_parser final:
	rule_parser,
	std::enable_shared_from_this<flag_assignable_parser>
{
	explicit flag_assignable_parser(const ast_node_flag flag);
	rule_parser::pointer operator=(rule_parser::pointer parser);
	parsing_result parse(const gsl::span<lexer::token>& tokens) const override;

private:
	const ast_node_flag flag;
	rule_parser::pointer parser;
};

}
}
}
#endif
