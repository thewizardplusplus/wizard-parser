#ifndef THEWIZARDPLUSPLUS_WIZARD_PARSER_PARSER_OPTIONAL_PARSER_HEADER
#define THEWIZARDPLUSPLUS_WIZARD_PARSER_PARSER_OPTIONAL_PARSER_HEADER

#include "empty_parser.hpp"
#include "rule_parser.hpp"
#include "parsing_result.hpp"

namespace thewizardplusplus {
namespace wizard_parser {
namespace parser {

struct optional_parser final: empty_parser {
	explicit optional_parser(rule_parser::pointer parser);

protected:
	virtual bool is_empty_result(
		const parsing_result& result
	) const override final;
};

namespace operators {

rule_parser::pointer operator-(rule_parser::pointer parser);

}
}
}
}
#endif
