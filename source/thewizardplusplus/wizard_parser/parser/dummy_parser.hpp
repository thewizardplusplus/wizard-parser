#ifndef THEWIZARDPLUSPLUS_WIZARD_PARSER_PARSER_DUMMY_PARSER_HEADER
#define THEWIZARDPLUSPLUS_WIZARD_PARSER_PARSER_DUMMY_PARSER_HEADER

#include "rule_parser.hpp"
#include "../lexer/token.hpp"
#include <memory>

namespace thewizardplusplus::wizard_parser::parser {

struct dummy_parser final: rule_parser {
	void set_parser(rule_parser::weak_pointer parser);
	virtual parsing_result parse(
		const lexer::token_span& tokens
	) const override final;

private:
	rule_parser::weak_pointer parser;
};

std::shared_ptr<dummy_parser> dummy();

}
#endif
