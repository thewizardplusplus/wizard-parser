#ifndef LEXER_TOKEN_HEADER
#define LEXER_TOKEN_HEADER

#include <string>
#include <cstddef>
#include <ostream>

namespace lexer {

struct token {
	std::string type;
	std::string value;
	std::size_t offset;
};

std::ostream& operator<<(std::ostream& out, const token& some_token);

}
#endif
