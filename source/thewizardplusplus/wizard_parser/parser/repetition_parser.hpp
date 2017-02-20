#ifndef THEWIZARDPLUSPLUS_WIZARD_PARSER_PARSER_REPETITION_PARSER_HEADER
#define THEWIZARDPLUSPLUS_WIZARD_PARSER_PARSER_REPETITION_PARSER_HEADER

#include "rule_parser.hpp"
#include "../lexer/token_group.hpp"
#include "parsing_result.hpp"

namespace thewizardplusplus {
namespace wizard_parser {
namespace parser {

struct repetition_parser final: rule_parser {
	explicit repetition_parser(rule_parser::pointer parser);
	virtual parsing_result parse(
		const lexer::token_group::const_iterator& begin,
		const lexer::token_group::const_iterator& end
	) const override final;

private:
	const rule_parser::pointer parser;
};

namespace operators {

rule_parser::pointer operator*(rule_parser::pointer parser);

}
}
}
}
#endif
