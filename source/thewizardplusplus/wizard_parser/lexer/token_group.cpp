#include "token_group.hpp"
#include <iterator>

namespace lexer {

std::ostream& operator<<(std::ostream& out, const token_group& tokens) {
	out << '[';

	for (
		auto token = std::cbegin(tokens);
		token != std::cend(tokens);
		++token
	) {
		if (token != std::cbegin(tokens)) {
			out << ',';
		}
		out << *token;
	}

	out << ']';
	return out;
}

}
