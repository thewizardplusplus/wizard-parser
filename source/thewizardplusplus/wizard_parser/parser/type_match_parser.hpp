#ifndef PARSER_TYPE_MATCH_PARSER_HEADER
#define PARSER_TYPE_MATCH_PARSER_HEADER

#include "match_parser.hpp"
#include "../lexer/token.hpp"
#include "rule_parser.hpp"
#include <string>
#include <cstddef>

namespace parser {

struct type_match_parser final: match_parser {
	explicit type_match_parser(std::string lexeme_type);

protected:
	virtual bool is_match(const lexer::token& token) const override final;
};

rule_parser::pointer operator""_t(const char* const lexeme_type, std::size_t);

}
#endif
