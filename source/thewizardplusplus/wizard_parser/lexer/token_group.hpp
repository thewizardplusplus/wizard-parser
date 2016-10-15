#ifndef LEXER_TOKEN_GROUP_HEADER
#define LEXER_TOKEN_GROUP_HEADER

#include "token.hpp"
#include <list>
#include <ostream>

namespace lexer {

using token_group = std::list<token>;

std::ostream& operator<<(std::ostream& out, const token_group& tokens);

}
#endif
