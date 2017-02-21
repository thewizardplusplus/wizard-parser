#include "token.hpp"
#include "../utilities/string_utilities.hpp"

using namespace std::string_literals;
using namespace thewizardplusplus::wizard_parser::utilities;

namespace thewizardplusplus {
namespace wizard_parser {
namespace lexer {

std::ostream& operator<<(std::ostream& out, const token& some_token) {
	out << to_string(some_token);
	return out;
}

std::string to_string(const token& some_token) {
	return "{"s
			+ R"("type":)" + quote(some_token.type) + ','
			+ R"("value":)" + quote(some_token.value)
		+ '}';
}

}
}
}
