#ifndef THEWIZARDPLUSPLUS_WIZARD_PARSER_PARSER_HIDE_PARSER_HEADER
#define THEWIZARDPLUSPLUS_WIZARD_PARSER_PARSER_HIDE_PARSER_HEADER

#include "rule_parser.hpp"
#include "../lexer/token.hpp"
#include "parsing_result.hpp"
#include "../vendor/gsl/span.hpp"

namespace thewizardplusplus {
namespace wizard_parser {
namespace parser {

struct hide_parser final: rule_parser {
	explicit hide_parser(rule_parser::pointer parser);
	parsing_result parse(const gsl::span<lexer::token>& tokens) const override;

private:
	const rule_parser::pointer parser;
};

namespace operators {

rule_parser::pointer operator&(rule_parser::pointer parser);

}
}
}
}
#endif
