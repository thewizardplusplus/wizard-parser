#ifndef THEWIZARDPLUSPLUS_WIZARD_PARSER_PARSER_UTILITIES_HEADER
#define THEWIZARDPLUSPLUS_WIZARD_PARSER_PARSER_UTILITIES_HEADER

#include "ast_node.hpp"
#include <limits>
#include <cstddef>

namespace thewizardplusplus::wizard_parser::parser {

const auto integral_infinity = std::numeric_limits<std::size_t>::max();

void append_node(ast_node_group& nodes, const ast_node& node);

}
#endif
