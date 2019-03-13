#ifndef THEWIZARDPLUSPLUS_WIZARD_PARSER_PARSER_AST_NODE_HEADER
#define THEWIZARDPLUSPLUS_WIZARD_PARSER_PARSER_AST_NODE_HEADER

#include "../vendor/better-enums/enum_strict.hpp"
#include <cstdint>
#include <optional>
#include <cstddef>
#include <string>
#include <vector>

namespace thewizardplusplus::wizard_parser::parser {

BETTER_ENUM(ast_node_type, std::uint8_t, sequence, nothing)

using optional_offset = std::optional<std::size_t>;

struct ast_node {
	std::string type;
	std::string value;
	std::vector<ast_node> children;
	optional_offset offset;
};

using ast_node_group = std::vector<ast_node>;

bool operator==(const ast_node& ast_1, const ast_node& ast_2);

}
#endif
