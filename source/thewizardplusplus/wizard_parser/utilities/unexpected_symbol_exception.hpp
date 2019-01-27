#ifndef THEWIZARDPLUSPLUS_WIZARD_PARSER_UTILITIES_UNEXPECTED_SYMBOL_EXCEPTION_HEADER
#define THEWIZARDPLUSPLUS_WIZARD_PARSER_UTILITIES_UNEXPECTED_SYMBOL_EXCEPTION_HEADER

#include "positional_exception.hpp"
#include <cstddef>

namespace thewizardplusplus::wizard_parser::utilities {

struct unexpected_symbol_exception: positional_exception {
	explicit unexpected_symbol_exception(const std::size_t& offset);
};

}
#endif
