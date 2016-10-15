#include "string_utilities.hpp"
#include <unordered_map>

const auto replacement_map = std::unordered_map<char, std::string>{
	{'"', R"(\")"},
	{'\\', R"(\\)"},
	{'\t', R"(\t)"},
	{'\n', R"(\n)"}
};

namespace utilities {

std::string quote(const std::string& string) {
	auto quoted_string = std::string{};
	for (const auto& symbol: string) {
		if (replacement_map.count(symbol)) {
			quoted_string += replacement_map.at(symbol);
		} else {
			quoted_string += symbol;
		}
	}

	return '"' + quoted_string + '"';
}

}
