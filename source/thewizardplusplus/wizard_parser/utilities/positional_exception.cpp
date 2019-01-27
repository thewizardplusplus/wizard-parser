#include "positional_exception.hpp"
#include "../vendor/fmt/format.hpp"

namespace thewizardplusplus::wizard_parser::utilities {

positional_exception::positional_exception(
	const std::string& description,
	const std::size_t& offset
):
	std::runtime_error{fmt::format("{:s} (offset: {:d})", description, offset)},
	description{description},
	offset{offset}
{}

}
