#include "Result.h"

const Result INVALID{false, "", {}, 0};

std::ostream& operator<<(std::ostream& stream, const Result& result) {
	if (result.valid) {
		stream << "{";

		auto has_value = false;
		if (!result.value.empty()) {
			stream << R"("value":")";
			for (const auto& symbol: result.value) {
				if (symbol == '"' || symbol == '\\' || symbol == '/') {
					stream << R"(\)";
				}
				stream << symbol;
			}
			stream << R"(")";

			has_value = true;
		}

		if (!result.children.empty()) {
			stream << (has_value ? "," : "") << R"("children":[)";
			for (size_t i = 0; i < result.children.size(); ++i) {
				stream << (i ? "," : "") << result.children[i];
			}
			stream << "]";
		}

		stream << "}";
	} else {
		stream << R"({"valid":false})";
	}

	return stream;
}
