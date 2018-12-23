#ifndef THEWIZARDPLUSPLUS_WIZARD_PARSER_PARSER_PARSERS_HEADER
#define THEWIZARDPLUSPLUS_WIZARD_PARSER_PARSER_PARSERS_HEADER

#include "empty_parser.hpp"
#include "eoi_parser.hpp"
#include "match_parser.hpp"
#include "concatenation_parser.hpp"
#include "alternation_parser.hpp"
#include "repetition_parser.hpp"
#include "exception_parser.hpp"
#include "lookahead_parser.hpp"
#include "dummy_parser.hpp"
#include "rule_parser.hpp"

namespace thewizardplusplus::wizard_parser::parser::operators {

rule_parser::pointer operator%(
	rule_parser::pointer left_parser,
	rule_parser::pointer right_parser
);

}
#endif
