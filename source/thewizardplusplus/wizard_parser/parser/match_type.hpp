#ifndef THEWIZARDPLUSPLUS_WIZARD_PARSER_PARSER_MATCH_TYPE_HEADER
#define THEWIZARDPLUSPLUS_WIZARD_PARSER_PARSER_MATCH_TYPE_HEADER

#include <cstdint>

namespace thewizardplusplus {
namespace wizard_parser {
namespace parser {

enum class match_type: std::uint8_t {
	by_type,
	by_value
};

}
}
}
#endif
