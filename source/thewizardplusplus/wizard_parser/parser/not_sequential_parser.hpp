#ifndef PARSER_NOT_SEQUENTIAL_PARSER_HEADER
#define PARSER_NOT_SEQUENTIAL_PARSER_HEADER

#include "binary_parser.hpp"
#include "rule_parser.hpp"

namespace parser {

struct not_sequential_parser: binary_parser {
	not_sequential_parser(
		rule_parser::pointer left_parser,
		rule_parser::pointer right_parser
	);

protected:
	virtual bool is_sequential() const override final;
};

}
#endif
