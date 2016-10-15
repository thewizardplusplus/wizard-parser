#ifndef PARSER_VALUE_MATCH_PARSER_HEADER
#define PARSER_VALUE_MATCH_PARSER_HEADER

#include "match_parser.hpp"
#include "../lexer/token.hpp"
#include "rule_parser.hpp"
#include <string>
#include <cstddef>

namespace parser {

struct value_match_parser final: match_parser {
	explicit value_match_parser(std::string string);

protected:
	virtual bool is_match(const lexer::token& token) const override final;
};

rule_parser::pointer operator""_v(const char* const string, std::size_t);

}
#endif
