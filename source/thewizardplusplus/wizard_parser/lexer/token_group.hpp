#ifndef THEWIZARDPLUSPLUS_WIZARD_PARSER_LEXER_TOKEN_GROUP_HEADER
#define THEWIZARDPLUSPLUS_WIZARD_PARSER_LEXER_TOKEN_GROUP_HEADER

#include "token.hpp"
#include "../vendor/json.hpp"
#include <list>
#include <ostream>
#include <string>

namespace thewizardplusplus {
namespace wizard_parser {
namespace lexer {

using token_group = std::list<token>;

std::ostream& operator<<(std::ostream& out, const token_group& tokens);
std::string to_string(const token_group& tokens);
nlohmann::json to_json(const token_group& tokens);

}
}
}
#endif
