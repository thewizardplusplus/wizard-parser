#include "set_utilities.hpp"

namespace utilities {

bool contains(
	const std::unordered_set<std::string>& set,
	const std::string& item
) {
	return set.count(item) != 0;
}

}
