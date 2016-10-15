#ifndef THEWIZARDPLUSPLUS_WIZARD_PARSER_PARSER_BINARY_PARSER_HEADER
#define THEWIZARDPLUSPLUS_WIZARD_PARSER_PARSER_BINARY_PARSER_HEADER

#include "rule_parser.hpp"
#include "../lexer/token_group.hpp"
#include "parsing_result.hpp"
#include <utility>

namespace thewizardplusplus {
namespace wizard_parser {
namespace parser {

struct binary_parser: rule_parser {
	binary_parser(
		rule_parser::pointer left_parser,
		rule_parser::pointer right_parser
	);
	virtual parsing_result parse(
		const lexer::token_group::const_iterator& begin,
		const lexer::token_group::const_iterator& end
	) const override final;

protected:
	virtual bool is_sequential() const = 0;
	virtual std::pair<parsing_result, bool> process_left_result(
		parsing_result result
	) const = 0;
	virtual std::pair<parsing_result, bool> process_right_result(
		parsing_result result
	) const = 0;
	virtual parsing_result combine_results(
		parsing_result left_result,
		parsing_result right_result,
		const lexer::token_group::const_iterator& end
	) const = 0;

private:
	const rule_parser::pointer left_parser;
	const rule_parser::pointer right_parser;
};

}
}
}
#endif
