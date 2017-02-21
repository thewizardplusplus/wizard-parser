#ifndef THEWIZARDPLUSPLUS_WIZARD_PARSER_LEXER_TOKEN_HEADER
#define THEWIZARDPLUSPLUS_WIZARD_PARSER_LEXER_TOKEN_HEADER

#include "../vendor/json.hpp"
#include <string>
#include <cstddef>
#include <ostream>

namespace thewizardplusplus {
namespace wizard_parser {
namespace lexer {

struct token {
	std::string type;
	std::string value;
	std::size_t offset;
};

std::ostream& operator<<(std::ostream& out, const token& some_token);
std::string to_string(const token& some_token);
nlohmann::json to_json(const token& some_token);

}
}
}
#endif
