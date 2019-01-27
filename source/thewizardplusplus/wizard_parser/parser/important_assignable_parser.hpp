#ifndef THEWIZARDPLUSPLUS_WIZARD_PARSER_PARSER_IMPORTANT_ASSIGNABLE_PARSER_HEADER
#define THEWIZARDPLUSPLUS_WIZARD_PARSER_PARSER_IMPORTANT_ASSIGNABLE_PARSER_HEADER

#include "assignable_parser.hpp"
#include "rule_parser.hpp"

namespace thewizardplusplus::wizard_parser::parser {

struct important_assignable_parser final: assignable_parser {
	using assignable_parser::operator=;

protected:
	parsing_result process_parsed_result(
		const parsing_result& result
	) const override;
};

}
#endif
