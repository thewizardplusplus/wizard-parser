#include "parsers.hpp"

namespace thewizardplusplus {
namespace wizard_parser {
namespace parser {
namespace operators {

rule_parser::pointer operator%(
	rule_parser::pointer left_parser,
	rule_parser::pointer right_parser
) {
	return left_parser >> *(right_parser >> left_parser);
}

}
}
}
}
