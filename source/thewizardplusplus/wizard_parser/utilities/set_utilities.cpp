#include "set_utilities.hpp"

namespace thewizardplusplus {
namespace wizard_parser {
namespace utilities {

bool contains(
	const std::unordered_set<std::string>& set,
	const std::string& item
) {
	return set.count(item) != 0;
}

}
}
}
