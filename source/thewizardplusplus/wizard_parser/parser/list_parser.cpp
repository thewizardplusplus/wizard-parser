#include "list_parser.hpp"
#include "concatenation_parser.hpp"
#include "repetition_parser.hpp"

namespace thewizardplusplus::wizard_parser::parser::operators {

rule_parser::pointer operator%(
	const rule_parser::pointer& parser,
	const rule_parser::pointer& separator
) {
	return parser >> *(separator >> parser);
}

}
