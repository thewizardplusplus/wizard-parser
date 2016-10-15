#include "not_sequential_parser.hpp"
#include <utility>

namespace parser {

not_sequential_parser::not_sequential_parser(
	rule_parser::pointer left_parser,
	rule_parser::pointer right_parser
):
	binary_parser{std::move(left_parser), std::move(right_parser)}
{}

bool not_sequential_parser::is_sequential() const {
	return false;
}

}
