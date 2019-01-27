#ifndef THEWIZARDPLUSPLUS_WIZARD_PARSER_PARSER_TYPE_ASSIGNABLE_PARSER_HEADER
#define THEWIZARDPLUSPLUS_WIZARD_PARSER_PARSER_TYPE_ASSIGNABLE_PARSER_HEADER

#include "assignable_parser.hpp"
#include "rule_parser.hpp"
#include <string>

namespace thewizardplusplus::wizard_parser::parser {

struct type_assignable_parser final: assignable_parser {
	using assignable_parser::operator=;

	explicit type_assignable_parser(const std::string& type);

private:
	const std::string type;

	parsing_result process_parsed_result(
		const parsing_result& result
	) const override;
};

}
#endif
