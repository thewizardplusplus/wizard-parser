#ifndef THEWIZARDPLUSPLUS_WIZARD_PARSER_PARSER_AST_NODE_HEADER
#define THEWIZARDPLUSPLUS_WIZARD_PARSER_PARSER_AST_NODE_HEADER

#include "../vendor/better-enums/enum_strict.hpp"
#include "../vendor/json.hpp"
#include <cstdint>
#include <optional>
#include <cstddef>
#include <string>
#include <vector>
#include <tuple>
#include <ostream>

namespace thewizardplusplus::wizard_parser::parser {

BETTER_ENUM(ast_node_type, std::uint8_t, sequence, nothing)

using offset_optional = std::optional<std::size_t>;

struct ast_node {
	std::string type;
	std::string value;
	std::vector<ast_node> children;
	offset_optional offset;
};

using ast_node_tuple =
	std::tuple<std::string, std::string, std::vector<ast_node>, offset_optional>;

using ast_node_group = std::vector<ast_node>;

bool operator==(const ast_node& ast_1, const ast_node& ast_2);
std::ostream& operator<<(std::ostream& stream, const ast_node& ast);
ast_node_tuple to_tuple(const ast_node& ast);
void to_json(nlohmann::json& json, const ast_node& ast);
std::size_t get_offset(const ast_node& ast);

}
#endif
