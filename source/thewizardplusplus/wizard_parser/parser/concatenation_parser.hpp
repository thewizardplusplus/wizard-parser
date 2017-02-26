#ifndef THEWIZARDPLUSPLUS_WIZARD_PARSER_PARSER_CONCATENATION_PARSER_HEADER
#define THEWIZARDPLUSPLUS_WIZARD_PARSER_PARSER_CONCATENATION_PARSER_HEADER

#include "sequential_parser.hpp"
#include "rule_parser.hpp"
#include "parsing_result.hpp"
#include <utility>

namespace thewizardplusplus {
namespace wizard_parser {
namespace parser {

struct concatenation_parser final: sequential_parser {
	concatenation_parser(
		rule_parser::pointer left_parser,
		rule_parser::pointer right_parser
	);

protected:
	virtual std::pair<parsing_result, bool> process_left_result(
		parsing_result result
	) const override final;
	virtual std::pair<parsing_result, bool> process_right_result(
		parsing_result result
	) const override final;
	virtual parsing_result combine_results(
		parsing_result left_result,
		parsing_result right_result
	) const override final;
};

namespace operators {

rule_parser::pointer operator>>(
	rule_parser::pointer left_parser,
	rule_parser::pointer right_parser
);

}
}
}
}
#endif
