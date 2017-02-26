#include "token_parser.hpp"

using namespace thewizardplusplus::wizard_parser::lexer;
using namespace gsl;

namespace thewizardplusplus {
namespace wizard_parser {
namespace parser {

parsing_result token_parser::parse(const span<token>& tokens) const {
	return !tokens.empty() ? parse_token(tokens) : parse_eoi();
}

}
}
}
