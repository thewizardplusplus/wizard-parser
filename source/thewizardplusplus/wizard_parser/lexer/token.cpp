#include "token.hpp"

using namespace nlohmann;

namespace thewizardplusplus {
namespace wizard_parser {
namespace lexer {

std::ostream& operator<<(std::ostream& out, const token& some_token) {
	out << to_string(some_token);
	return out;
}

std::string to_string(const token& some_token) {
	return to_json(some_token).dump();
}

json to_json(const token& some_token) {
	return {
		{"type", some_token.type},
		{"value", some_token.value}
	};
}

}
}
}
