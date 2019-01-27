#ifndef THEWIZARDPLUSPLUS_WIZARD_PARSER_UTILITIES_UNEXPECTED_ENTITY_EXCEPTION_HEADER
#define THEWIZARDPLUSPLUS_WIZARD_PARSER_UTILITIES_UNEXPECTED_ENTITY_EXCEPTION_HEADER

#include "positional_exception.hpp"
#include "../vendor/better-enums/enum_strict.hpp"
#include "../vendor/fmt/format.hpp"
#include <cstdint>
#include <cstddef>

namespace thewizardplusplus::wizard_parser::utilities {

BETTER_ENUM(entity_type, std::uint8_t, symbol, token, eoi)

template<entity_type::_integral type>
struct unexpected_entity_exception final: positional_exception {
	static_assert(entity_type::_is_valid(type));

	explicit unexpected_entity_exception(const std::size_t& offset);
};

template<entity_type::_integral type>
unexpected_entity_exception<type>::unexpected_entity_exception(
	const std::size_t& offset
):
	positional_exception{
		fmt::format(
			"unexpected {:s}",
			entity_type::_from_integral(type)._to_string()
		),
		offset
	}
{}

}
#endif
