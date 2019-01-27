#ifndef THEWIZARDPLUSPLUS_WIZARD_PARSER_PARSER_ASSIGNABLE_PARSER_HEADER
#define THEWIZARDPLUSPLUS_WIZARD_PARSER_PARSER_ASSIGNABLE_PARSER_HEADER

#include "rule_parser.hpp"
#include "../lexer/token.hpp"
#include <memory>

namespace thewizardplusplus::wizard_parser::parser {

struct assignable_parser:
	rule_parser,
	std::enable_shared_from_this<assignable_parser>
{
	rule_parser::pointer operator=(const rule_parser::pointer& parser);
	parsing_result parse(const lexer::token_span& tokens) const override;

protected:
	virtual parsing_result process_parsed_result(
		const parsing_result& result
	) const = 0;

private:
	rule_parser::pointer parser;
};

}
#endif
