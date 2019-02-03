#ifndef THEWIZARDPLUSPLUS_WIZARD_PARSER_PARSER_MACROSES_HEADER
#define THEWIZARDPLUSPLUS_WIZARD_PARSER_PARSER_MACROSES_HEADER

#include "type_assignable_parser.hpp"
#include <memory>

#define RULE(type) const auto type = \
	*std::make_shared< \
		thewizardplusplus::wizard_parser::parser::type_assignable_parser \
	>(#type)
#endif
