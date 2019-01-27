#ifndef THEWIZARDPLUSPLUS_WIZARD_PARSER_UTILITIES_POSITIONAL_EXCEPTION_HEADER
#define THEWIZARDPLUSPLUS_WIZARD_PARSER_UTILITIES_POSITIONAL_EXCEPTION_HEADER

#include <stdexcept>
#include <string>
#include <cstddef>

namespace thewizardplusplus::wizard_parser::utilities {

struct positional_exception: std::runtime_error {
	const std::string description;
	const std::size_t offset;

	positional_exception(
		const std::string& description,
		const std::size_t& offset
	);
};

}
#endif
