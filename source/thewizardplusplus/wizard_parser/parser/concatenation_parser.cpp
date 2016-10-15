#include "concatenation_parser.hpp"
#include "utilities.hpp"
#include <list>
#include <memory>

using namespace lexer;

namespace parser {

concatenation_parser::concatenation_parser(
	rule_parser::pointer left_parser,
	rule_parser::pointer right_parser
):
	sequential_parser{std::move(left_parser), std::move(right_parser)}
{}

std::pair<parsing_result, bool> concatenation_parser::process_left_result(
	parsing_result result
) const {
	return {std::move(result), result.is_parsed};
}

std::pair<parsing_result, bool> concatenation_parser::process_right_result(
	parsing_result result
) const {
	return {std::move(result), result.is_parsed};
}

parsing_result concatenation_parser::combine_results(
	parsing_result left_result,
	parsing_result right_result,
	const token_group::const_iterator& end
) const {
	static_cast<void>(end);

	auto nodes = std::list<ast_node>{};
	append_node(nodes, std::move(left_result.node));
	append_node(nodes, std::move(right_result.node));

	return {
		true,
		{"sequence", {}, std::move(nodes)},
		std::move(right_result.last_token)
	};
}

rule_parser::pointer operator>>(
	rule_parser::pointer left_parser,
	rule_parser::pointer right_parser
) {
	return std::make_shared<concatenation_parser>(
		std::move(left_parser),
		std::move(right_parser)
	);
}

}
