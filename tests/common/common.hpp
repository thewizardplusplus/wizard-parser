#ifndef TESTS_COMMON_COMMON_HEADER
#define TESTS_COMMON_COMMON_HEADER

#include "../../source/thewizardplusplus/wizard_parser/parser/rule_parser.hpp"
#include <string>

namespace tests::common {

using namespace thewizardplusplus::wizard_parser;

parser::parsing_result ast_with_type(
	const parser::parsing_result& ast,
	const std::string& type
);

}
#endif
