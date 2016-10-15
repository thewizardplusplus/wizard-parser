#ifndef THEWIZARDPLUSPLUS_WIZARD_PARSER_PARSER_UTILITIES_HEADER
#define THEWIZARDPLUSPLUS_WIZARD_PARSER_PARSER_UTILITIES_HEADER

#include "lift_parser.hpp"
#include "type_assignable_parser.hpp"
#include "ast_node_flag.hpp"
#include "flag_assignable_parser.hpp"
#include "ast_node.hpp"
#include <memory>
#include <list>

#define RULE(type) const auto type = \
	*std::make_shared<type_assignable_parser>(#type) = \
	*std::make_shared<lift_parser>()
#define IMPORTANT_RULE(type) const auto type = \
	*std::make_shared<flag_assignable_parser>(ast_node_flag::important) = \
	*std::make_shared<type_assignable_parser>(#type)

namespace parser {

void append_node(std::list<ast_node>& nodes, ast_node&& node);

}
#endif
