#ifndef THEWIZARDPLUSPLUS_WIZARD_PARSER_UTILITIES_UNEXPECTED_EOI_EXCEPTION_HEADER
#define THEWIZARDPLUSPLUS_WIZARD_PARSER_UTILITIES_UNEXPECTED_EOI_EXCEPTION_HEADER

#include "positional_exception.hpp"
#include <cstddef>

namespace thewizardplusplus::wizard_parser::utilities {

struct unexpected_eoi_exception: positional_exception {
	explicit unexpected_eoi_exception(const std::size_t& offset);
};

}
#endif
