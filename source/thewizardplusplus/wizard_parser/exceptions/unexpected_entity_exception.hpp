#ifndef THEWIZARDPLUSPLUS_WIZARD_PARSER_EXCEPTIONS_UNEXPECTED_ENTITY_EXCEPTION_HEADER
#define THEWIZARDPLUSPLUS_WIZARD_PARSER_EXCEPTIONS_UNEXPECTED_ENTITY_EXCEPTION_HEADER

#include "positional_exception.hpp"
#include "../vendor/fmt/format.hpp"
#include "../vendor/better-enums/enum_strict.hpp"
#include <cstddef>
#include <cstdint>

namespace thewizardplusplus::wizard_parser::exceptions {

template<typename entity_type, typename entity_type::_integral type>
struct base_unexpected_entity_exception final: positional_exception {
	static_assert(entity_type::_is_valid(type));

	explicit base_unexpected_entity_exception(const std::size_t& offset);
};

template<typename entity_type, typename entity_type::_integral type>
base_unexpected_entity_exception<entity_type, type>::
	base_unexpected_entity_exception(const std::size_t& offset):
		positional_exception{
			fmt::format(
				"unexpected {:s}",
				entity_type::_from_integral(type)._to_string()
			),
			offset
		}
	{}

BETTER_ENUM(entity_type, std::uint8_t, symbol, token, eoi)

template<entity_type::_integral type>
using unexpected_entity_exception =
	base_unexpected_entity_exception<entity_type, type>;

}
#endif
