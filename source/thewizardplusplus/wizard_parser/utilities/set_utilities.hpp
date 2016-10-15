#ifndef THEWIZARDPLUSPLUS_WIZARD_PARSER_UTILITIES_SET_UTILITIES_HEADER
#define THEWIZARDPLUSPLUS_WIZARD_PARSER_UTILITIES_SET_UTILITIES_HEADER

#include <unordered_set>
#include <string>

namespace thewizardplusplus {
namespace wizard_parser {
namespace utilities {

bool contains(
	const std::unordered_set<std::string>& set,
	const std::string& item
);

}
}
}
#endif
