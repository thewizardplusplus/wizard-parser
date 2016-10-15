#include "token.hpp"
#include "../utilities/string_utilities.hpp"

using namespace utilities;

namespace lexer {

std::ostream& operator<<(std::ostream& out, const token& some_token) {
	out << '{'
			<< R"("type":)" << quote(some_token.type) << ','
			<< R"("value":)" << quote(some_token.value)
		<< '}';

	return out;
}

}
