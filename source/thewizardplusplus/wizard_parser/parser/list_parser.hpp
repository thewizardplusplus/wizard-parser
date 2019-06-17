#ifndef THEWIZARDPLUSPLUS_WIZARD_PARSER_PARSER_LIST_PARSER_HEADER
#define THEWIZARDPLUSPLUS_WIZARD_PARSER_PARSER_LIST_PARSER_HEADER

#include "rule_parser.hpp"

namespace thewizardplusplus::wizard_parser::parser::operators {

rule_parser::pointer operator%(
	const rule_parser::pointer& parser,
	const rule_parser::pointer& separator
);

}
#endif
