#ifndef THEWIZARDPLUSPLUS_WIZARD_PARSER_LEXER_TOKEN_HEADER
#define THEWIZARDPLUSPLUS_WIZARD_PARSER_LEXER_TOKEN_HEADER

#include "../vendor/gsl/span.hpp"
#include "../vendor/json.hpp"
#include <string>
#include <cstddef>
#include <tuple>
#include <vector>
#include <ostream>

namespace thewizardplusplus::wizard_parser::lexer {

struct token {
	std::string type;
	std::string value;
	std::size_t offset;
};

using token_tuple = std::tuple<std::string, std::string, std::size_t>;

using token_group = std::vector<token>;

using token_span = gsl::span<token>;

bool operator==(const token& token_1, const token& token_2);
std::ostream& operator<<(std::ostream& stream, const token& some_token);
token_tuple to_tuple(const token& some_token);
void to_json(nlohmann::json& json, const token& some_token);
std::size_t get_offset(const token_span& tokens);

}
#endif
