#include "type_match_parser.hpp"
#include <utility>
#include <memory>

using namespace lexer;

namespace parser {

type_match_parser::type_match_parser(std::string lexeme_type):
	match_parser{std::move(lexeme_type)}
{}

bool type_match_parser::is_match(const token& token) const {
	return token.type == sample;
}

rule_parser::pointer operator""_t(const char* const lexeme_type, std::size_t) {
	return std::make_shared<type_match_parser>(lexeme_type);
}

}
