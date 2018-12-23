#include "token_group.hpp"
#include <iterator>
#include <algorithm>

using namespace nlohmann;

namespace thewizardplusplus::wizard_parser::lexer {

std::ostream& operator<<(std::ostream& out, const token_group& tokens) {
	out << to_string(tokens);
	return out;
}

std::string to_string(const token_group& tokens) {
	return to_json(tokens).dump();
}

json to_json(const token_group& tokens) {
	auto result = json{};
	std::for_each(
		std::cbegin(tokens),
		std::cend(tokens),
		[&result] (const auto& token) {
			result.push_back(to_json(token));
		}
	);

	return result;
}

}
