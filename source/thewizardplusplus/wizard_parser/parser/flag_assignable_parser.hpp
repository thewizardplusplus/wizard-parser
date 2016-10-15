#ifndef PARSER_FLAG_ASSIGNABLE_PARSER_HEADER
#define PARSER_FLAG_ASSIGNABLE_PARSER_HEADER

#include "assignable_parser.hpp"
#include "ast_node_flag.hpp"
#include "parsing_result.hpp"

namespace parser {

struct flag_assignable_parser final: assignable_parser {
	using assignable_parser::operator=;

	explicit flag_assignable_parser(const ast_node_flag flag);

protected:
	virtual parsing_result process_parsed_result(
		parsing_result result
	) const override final;

private:
	const ast_node_flag flag;
};

}
#endif
