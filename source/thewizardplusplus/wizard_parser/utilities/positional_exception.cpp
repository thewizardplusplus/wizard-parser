#include "positional_exception.hpp"
#include <utility>

namespace thewizardplusplus {
namespace wizard_parser {
namespace utilities {

positional_exception::positional_exception(
	std::string description,
	const std::size_t offset
):
	std::runtime_error{
		description + " (offset: " + std::to_string(offset) + ')'
	},
	description{std::move(description)},
	offset{offset}
{}

}
}
}
