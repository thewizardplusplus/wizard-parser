#include "token.hpp"
#include <algorithm>
#include <iterator>

namespace thewizardplusplus::wizard_parser::lexer {

std::ostream& operator<<(std::ostream& out, const token& some_token) {
	out << to_string(some_token);
	return out;
}

std::ostream& operator<<(std::ostream& out, const token_group& tokens) {
	out << to_string(tokens);
	return out;
}

std::string to_string(const token& some_token) {
	return to_json(some_token).dump();
}

std::string to_string(const token_group& tokens) {
	return to_json(tokens).dump();
}

nlohmann::json to_json(const token& some_token) {
	return { { "type", some_token.type }, { "value", some_token.value } };
}

nlohmann::json to_json(const token_group& tokens) {
	auto result = nlohmann::json{};
	std::for_each(
		std::cbegin(tokens),
		std::cend(tokens),
		[&] (const auto& token) { result.push_back(to_json(token)); }
	);

	return result;
}

}
