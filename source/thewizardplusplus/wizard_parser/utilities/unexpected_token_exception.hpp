#ifndef THEWIZARDPLUSPLUS_WIZARD_PARSER_UTILITIES_UNEXPECTED_TOKEN_EXCEPTION_HEADER
#define THEWIZARDPLUSPLUS_WIZARD_PARSER_UTILITIES_UNEXPECTED_TOKEN_EXCEPTION_HEADER

#include "positional_exception.hpp"
#include <cstddef>

namespace thewizardplusplus::wizard_parser::utilities {

struct unexpected_token_exception: positional_exception {
	explicit unexpected_token_exception(const std::size_t& offset);
};

}
#endif
