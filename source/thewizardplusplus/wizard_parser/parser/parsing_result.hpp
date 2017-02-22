#ifndef THEWIZARDPLUSPLUS_WIZARD_PARSER_PARSER_PARSING_RESULT_HEADER
#define THEWIZARDPLUSPLUS_WIZARD_PARSER_PARSER_PARSING_RESULT_HEADER

#include "ast_node.hpp"
#include "../lexer/token_group.hpp"
#include "../vendor/optional.hpp"
#include <cstddef>

namespace thewizardplusplus {
namespace wizard_parser {
namespace parser {

struct parsing_result {
	std::experimental::optional<ast_node> node;
	lexer::token_group::const_iterator last_token;

	std::size_t get_last_token_offset(
		const lexer::token_group::const_iterator& end
	) const;
};

}
}
}
#endif
