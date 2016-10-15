#ifndef THEWIZARDPLUSPLUS_WIZARD_PARSER_PARSER_TYPE_ASSIGNABLE_PARSER_HEADER
#define THEWIZARDPLUSPLUS_WIZARD_PARSER_PARSER_TYPE_ASSIGNABLE_PARSER_HEADER

#include "assignable_parser.hpp"
#include "parsing_result.hpp"
#include <string>

namespace parser {

struct type_assignable_parser final: assignable_parser {
	using assignable_parser::operator=;

	explicit type_assignable_parser(std::string type);

protected:
	virtual parsing_result process_parsed_result(
		parsing_result result
	) const override final;

private:
	const std::string type;
};

}
#endif
