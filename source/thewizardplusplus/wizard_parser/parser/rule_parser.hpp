#ifndef THEWIZARDPLUSPLUS_WIZARD_PARSER_PARSER_RULE_PARSER_HEADER
#define THEWIZARDPLUSPLUS_WIZARD_PARSER_PARSER_RULE_PARSER_HEADER

#include "../lexer/token.hpp"
#include "parsing_result.hpp"
#include "../vendor/gsl/span.hpp"
#include <memory>
#include <initializer_list>

namespace thewizardplusplus::wizard_parser::parser {

struct rule_parser {
	using pointer = std::shared_ptr<const rule_parser>;
	using weak_pointer = std::weak_ptr<const rule_parser>;
	using initializer_list = std::initializer_list<pointer>;

	virtual ~rule_parser();
	virtual parsing_result parse(
		const gsl::span<lexer::token>& tokens
	) const = 0;
};

}
#endif
