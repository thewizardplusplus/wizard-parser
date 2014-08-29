#include "Node.h"

std::ostream& operator<<(std::ostream& stream, const Node& node) {
	stream << "{";

	auto has_value = false;
	if (!node.value.empty()) {
		stream << R"("value":")";
		for (const auto& symbol: node.value) {
			stream
				<< (symbol == '"' || symbol == '\\' || symbol == '/'
					? R"(\)"
					: "")
				<< symbol;
		}
		stream << R"(")";

		has_value = true;
	}

	if (!node.children.empty()) {
		stream << (has_value ? "," : "") << R"("children":[)";
		for (size_t i = 0; i < node.children.size(); ++i) {
			stream << (i ? "," : "") << node.children[i];
		}
		stream << "]";
	}

	stream << "}";
	return stream;
}
