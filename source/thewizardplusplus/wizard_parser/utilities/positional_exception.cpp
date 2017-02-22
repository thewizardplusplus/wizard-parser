#include "positional_exception.hpp"
#include "../vendor/fmt/format.hpp"
#include <utility>

using namespace fmt;

namespace thewizardplusplus {
namespace wizard_parser {
namespace utilities {

positional_exception::positional_exception(
	std::string description,
	const std::size_t offset
):
	std::runtime_error{format("{:s} (offset: {:d})", description, offset)},
	description{std::move(description)},
	offset{offset}
{}

}
}
}
