#ifndef THEWIZARDPLUSPLUS_WIZARD_PARSER_PARSER_EMPTY_PARSER_HEADER
#define THEWIZARDPLUSPLUS_WIZARD_PARSER_PARSER_EMPTY_PARSER_HEADER

#include "wrapping_parser.hpp"
#include "rule_parser.hpp"
#include "parsing_result.hpp"

namespace thewizardplusplus {
namespace wizard_parser {
namespace parser {

struct empty_parser: wrapping_parser {
	explicit empty_parser(rule_parser::pointer parser);

protected:
	virtual parsing_result process_result(
		parsing_result result
	) const override final;
	virtual bool is_empty_result(const parsing_result& result) const = 0;
};

}
}
}
#endif
