#include "parsing_result.hpp"
#include <limits>

namespace thewizardplusplus {
namespace wizard_parser {
namespace parser {

std::size_t parsing_result::get_last_token_offset() const {
	return !this->rest_tokens.empty()
		? this->rest_tokens[0].offset
		: std::numeric_limits<std::size_t>::max();
}

}
}
}
