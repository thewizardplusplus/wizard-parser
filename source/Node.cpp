#include "Node.h"

static std::string escape(const std::string& text) {
	auto escaped_text = std::string();
	for (const auto& symbol: text) {
		escaped_text +=
			(symbol == '"' || symbol == '\\' || symbol == '/'
				? std::string(R"(\)")
				: std::string())
			+ symbol;
	}

	return escaped_text;
}

std::ostream& operator<<(std::ostream& stream, const Node& node) {
	stream << "{";
	if (!node.name.empty()) {
		stream << R"("name":")" << escape(node.name) << R"(")";
	}
	if (!node.value.empty()) {
		stream
			<< (!node.name.empty() ? "," : "")
			<< R"("value":")" << escape(node.value) << R"(")";
	}
	if (!node.children.empty()) {
		stream
			<< (!node.name.empty() || !node.value.empty() ? "," : "")
			<< R"("children":[)";
		for (size_t i = 0; i < node.children.size(); ++i) {
			stream << (i ? "," : "") << node.children[i];
		}
		stream << "]";
	}
	stream << "}";

	return stream;
}
