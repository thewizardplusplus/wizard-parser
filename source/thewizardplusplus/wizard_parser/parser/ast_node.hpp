#ifndef THEWIZARDPLUSPLUS_WIZARD_PARSER_PARSER_AST_NODE_HEADER
#define THEWIZARDPLUSPLUS_WIZARD_PARSER_PARSER_AST_NODE_HEADER

#include "ast_node_flag.hpp"
#include "../vendor/json.hpp"
#include <string>
#include <vector>
#include <ostream>

namespace thewizardplusplus {
namespace wizard_parser {
namespace parser {

struct ast_node {
	std::string type;
	std::string value;
	std::vector<ast_node> children;
	ast_node_flag flags = ast_node_flag::none;
};

std::ostream& operator<<(std::ostream& out, const ast_node& ast);
std::string to_string(const ast_node& ast);
nlohmann::json to_json(const ast_node& ast);

}
}
}
#endif
