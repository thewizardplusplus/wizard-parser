#ifndef THEWIZARDPLUSPLUS_WIZARD_PARSER_PARSER_TYPE_ASSIGNABLE_PARSER_HEADER
#define THEWIZARDPLUSPLUS_WIZARD_PARSER_PARSER_TYPE_ASSIGNABLE_PARSER_HEADER

#include "rule_parser.hpp"
#include "../lexer/token.hpp"
#include <memory>
#include <string>

namespace thewizardplusplus::wizard_parser::parser {

struct type_assignable_parser final:
	rule_parser,
	std::enable_shared_from_this<type_assignable_parser>
{
	explicit type_assignable_parser(const std::string& type);
	rule_parser::pointer operator=(const rule_parser::pointer& parser);
	parsing_result parse(const lexer::token_span& tokens) const override;

private:
	const std::string type;
	rule_parser::pointer parser;
};

}
#endif
