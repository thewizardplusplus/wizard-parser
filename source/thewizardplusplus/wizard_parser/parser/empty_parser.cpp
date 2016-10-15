#include "empty_parser.hpp"
#include <utility>

namespace parser {

empty_parser::empty_parser(rule_parser::pointer parser):
	wrapping_parser{std::move(parser)}
{}

parsing_result empty_parser::process_result(parsing_result result) const {
	return is_empty_result(result)
		? parsing_result{
			true,
			{"nothing", {}, {}},
			std::move(result.last_token)
		}
		: result;
}

}
