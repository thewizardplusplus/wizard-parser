#include "token_group.hpp"
#include <iterator>

using namespace std::string_literals;

namespace thewizardplusplus {
namespace wizard_parser {
namespace lexer {

std::ostream& operator<<(std::ostream& out, const token_group& tokens) {
	out << to_string(tokens);
	return out;
}

std::string to_string(const token_group& tokens) {
	auto result = "["s;

	for (
		auto token = std::cbegin(tokens);
		token != std::cend(tokens);
		++token
	) {
		if (token != std::cbegin(tokens)) {
			result += ',';
		}
		result += to_string(*token);
	}

	result += ']';
	return result;
}

}
}
}
