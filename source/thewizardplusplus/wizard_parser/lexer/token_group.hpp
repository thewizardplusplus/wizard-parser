#ifndef THEWIZARDPLUSPLUS_WIZARD_PARSER_LEXER_TOKEN_GROUP_HEADER
#define THEWIZARDPLUSPLUS_WIZARD_PARSER_LEXER_TOKEN_GROUP_HEADER

#include "token.hpp"
#include "../vendor/json.hpp"
#include <vector>
#include <ostream>
#include <string>

namespace thewizardplusplus::wizard_parser::lexer {

using token_group = std::vector<token>;

std::ostream& operator<<(std::ostream& out, const token_group& tokens);
std::string to_string(const token_group& tokens);
nlohmann::json to_json(const token_group& tokens);

}
#endif
