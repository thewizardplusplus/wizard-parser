#include "unexpected_eoi_exception.hpp"

namespace thewizardplusplus::wizard_parser::utilities {

unexpected_eoi_exception::unexpected_eoi_exception(const std::size_t& offset):
	positional_exception{"unexpected EOI", offset}
{}

}
