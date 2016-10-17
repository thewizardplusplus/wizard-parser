#ifndef THEWIZARDPLUSPLUS_WIZARD_PARSER_PARSER_SEQUENTIAL_PARSER_HEADER
#define THEWIZARDPLUSPLUS_WIZARD_PARSER_PARSER_SEQUENTIAL_PARSER_HEADER

#include "binary_parser.hpp"
#include "rule_parser.hpp"

namespace thewizardplusplus {
namespace wizard_parser {
namespace parser {

struct sequential_parser: binary_parser {
	sequential_parser(
		rule_parser::pointer left_parser,
		rule_parser::pointer right_parser
	);

protected:
	virtual bool is_sequential() const override final;
};

}
}
}
#endif