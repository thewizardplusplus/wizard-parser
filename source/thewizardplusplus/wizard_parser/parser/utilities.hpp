#ifndef THEWIZARDPLUSPLUS_WIZARD_PARSER_PARSER_UTILITIES_HEADER
#define THEWIZARDPLUSPLUS_WIZARD_PARSER_PARSER_UTILITIES_HEADER

#include "ast_node.hpp"
#include <list>

namespace thewizardplusplus {
namespace wizard_parser {
namespace parser {

void append_node(std::list<ast_node>& nodes, ast_node&& node);

}
}
}
#endif
