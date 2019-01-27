#ifndef THEWIZARDPLUSPLUS_WIZARD_PARSER_LEXER_TOKEN_HEADER
#define THEWIZARDPLUSPLUS_WIZARD_PARSER_LEXER_TOKEN_HEADER

#include "../vendor/gsl/span.hpp"
#include "../vendor/json.hpp"
#include <string>
#include <cstddef>
#include <ostream>
#include <vector>

namespace thewizardplusplus::wizard_parser::lexer {

struct token {
	std::string type;
	std::string value;
	std::size_t offset;
};

using token_group = std::vector<token>;

using token_span = gsl::span<token>;

std::ostream& operator<<(std::ostream& out, const token& some_token);
std::ostream& operator<<(std::ostream& out, const token_group& tokens);
std::string to_string(const token& some_token);
std::string to_string(const token_group& tokens);
nlohmann::json to_json(const token& some_token);
nlohmann::json to_json(const token_group& tokens);

}
#endif
