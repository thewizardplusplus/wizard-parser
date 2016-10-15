#ifndef THEWIZARDPLUSPLUS_WIZARD_PARSER_PARSER_ASSIGNABLE_PARSER_HEADER
#define THEWIZARDPLUSPLUS_WIZARD_PARSER_PARSER_ASSIGNABLE_PARSER_HEADER

#include "wrapping_parser.hpp"
#include "rule_parser.hpp"
#include "parsing_result.hpp"
#include <memory>

namespace parser {

struct assignable_parser:
	wrapping_parser,
	std::enable_shared_from_this<assignable_parser>
{
	rule_parser::pointer operator=(rule_parser::pointer parser);

protected:
	virtual parsing_result process_result(
		parsing_result result
	) const override final;
	virtual parsing_result process_parsed_result(
		parsing_result result
	) const = 0;
};

}
#endif
