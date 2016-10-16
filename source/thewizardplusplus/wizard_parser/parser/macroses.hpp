#ifndef THEWIZARDPLUSPLUS_WIZARD_PARSER_PARSER_MACROSES_HEADER
#define THEWIZARDPLUSPLUS_WIZARD_PARSER_PARSER_MACROSES_HEADER

#include "lift_parser.hpp"
#include "type_assignable_parser.hpp"
#include "ast_node_flag.hpp"
#include "flag_assignable_parser.hpp"
#include <memory>

#define RULE(type) const auto type = \
	*std::make_shared< \
		thewizardplusplus::wizard_parser::parser::type_assignable_parser \
	>(#type) = \
	*std::make_shared<thewizardplusplus::wizard_parser::parser::lift_parser>()
#define IMPORTANT_RULE(type) const auto type = \
	*std::make_shared< \
		thewizardplusplus::wizard_parser::parser::flag_assignable_parser \
	>(thewizardplusplus::wizard_parser::parser::ast_node_flag::important) = \
	*std::make_shared< \
		thewizardplusplus::wizard_parser::parser::type_assignable_parser \
	>(#type)
#endif
