#ifndef THEWIZARDPLUSPLUS_WIZARD_PARSER_PARSER_DUMMY_PARSER_HEADER
#define THEWIZARDPLUSPLUS_WIZARD_PARSER_PARSER_DUMMY_PARSER_HEADER

#include "rule_parser.hpp"
#include "../lexer/token.hpp"
#include <memory>

namespace thewizardplusplus::wizard_parser::parser {

struct dummy_parser final: rule_parser {
	using pointer = std::shared_ptr<dummy_parser>;

	void set_parser(const rule_parser::weak_pointer& parser);
	parsing_result parse(const lexer::token_span& tokens) const override;

private:
	rule_parser::weak_pointer parser;
};

dummy_parser::pointer dummy();

}
#endif
