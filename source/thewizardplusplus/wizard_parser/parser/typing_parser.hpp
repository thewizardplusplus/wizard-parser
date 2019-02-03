#ifndef THEWIZARDPLUSPLUS_WIZARD_PARSER_PARSER_TYPING_PARSER_HEADER
#define THEWIZARDPLUSPLUS_WIZARD_PARSER_PARSER_TYPING_PARSER_HEADER

#include "rule_parser.hpp"
#include "../lexer/token.hpp"
#include <memory>
#include <string>

namespace thewizardplusplus::wizard_parser::parser {

struct typing_parser final:
	rule_parser,
	std::enable_shared_from_this<typing_parser>
{
	explicit typing_parser(const std::string& type);
	rule_parser::pointer operator=(const rule_parser::pointer& parser);
	parsing_result parse(const lexer::token_span& tokens) const override;

private:
	const std::string type;
	rule_parser::pointer parser;
};

}

#ifdef THEWIZARDPLUSPLUS_WIZARD_PARSER_PARSER_MACROSES
#define RULE(type) const auto type = \
	*std::make_shared<thewizardplusplus::wizard_parser::parser::typing_parser>( \
		#type \
	)
#endif
#endif
