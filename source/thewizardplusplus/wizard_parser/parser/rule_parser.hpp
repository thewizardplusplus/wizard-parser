#ifndef THEWIZARDPLUSPLUS_WIZARD_PARSER_PARSER_RULE_PARSER_HEADER
#define THEWIZARDPLUSPLUS_WIZARD_PARSER_PARSER_RULE_PARSER_HEADER

#include "ast_node.hpp"
#include "../lexer/token.hpp"
#include <optional>
#include <memory>
#include <initializer_list>

namespace thewizardplusplus::wizard_parser::parser {

struct parsing_result {
	std::optional<ast_node> node;
	lexer::token_span rest_tokens;
};

struct rule_parser {
	using pointer = std::shared_ptr<const rule_parser>;
	using weak_pointer = std::weak_ptr<const rule_parser>;
	using initializer_list = std::initializer_list<pointer>;

	virtual ~rule_parser();
	virtual parsing_result parse(const lexer::token_span& tokens) const = 0;
};

}
#endif
