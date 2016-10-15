#ifndef PARSER_LIFT_PARSER_HEADER
#define PARSER_LIFT_PARSER_HEADER

#include "assignable_parser.hpp"
#include "parsing_result.hpp"

namespace parser {

struct lift_parser final: assignable_parser {
	using assignable_parser::operator=;

protected:
	virtual parsing_result process_parsed_result(
		parsing_result result
	) const override final;
};

}
#endif
