#include "sequential_parser.hpp"
#include <utility>

namespace parser {

sequential_parser::sequential_parser(
	rule_parser::pointer left_parser,
	rule_parser::pointer right_parser
):
	binary_parser{std::move(left_parser), std::move(right_parser)}
{}

bool sequential_parser::is_sequential() const {
	return true;
}

}
