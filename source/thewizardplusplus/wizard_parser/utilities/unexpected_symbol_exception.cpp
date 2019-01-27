#include "unexpected_symbol_exception.hpp"

namespace thewizardplusplus::wizard_parser::utilities {

unexpected_symbol_exception::unexpected_symbol_exception(
	const std::size_t& offset
):
	positional_exception{"unexpected symbol", offset}
{}

}
