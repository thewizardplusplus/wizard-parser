#ifndef THEWIZARDPLUSPLUS_WIZARD_PARSER_PARSER_LIFT_PARSER_HEADER
#define THEWIZARDPLUSPLUS_WIZARD_PARSER_PARSER_LIFT_PARSER_HEADER

#include "rule_parser.hpp"
#include "../lexer/token.hpp"
#include "parsing_result.hpp"
#include "../vendor/gsl/span.hpp"
#include <memory>

namespace thewizardplusplus {
namespace wizard_parser {
namespace parser {

struct lift_parser final:
	rule_parser,
	std::enable_shared_from_this<lift_parser>
{
	rule_parser::pointer operator=(rule_parser::pointer parser);
	parsing_result parse(const gsl::span<lexer::token>& tokens) const override;

private:
	rule_parser::pointer parser;
};

}
}
}
#endif
