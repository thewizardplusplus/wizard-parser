#include "unexpected_token_exception.hpp"

namespace thewizardplusplus::wizard_parser::utilities {

unexpected_token_exception::unexpected_token_exception(
	const std::size_t& offset
):
	positional_exception{"unexpected token", offset}
{}

}
