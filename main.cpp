#include <vector>
#include <functional>
#include <iostream>

struct Result {
	bool valid;
	std::string value;
	std::vector<Result> children;
	size_t position;
};
using Parser = std::function<Result(const std::string&, const size_t&)>;

const auto invalid = Result();
const auto symbol = [] (const char& symbol) {
	return [=] (const std::string& text, const size_t& position) -> Result {
		return text.size() > position && text[position] == symbol
			? Result{true, std::string(1, symbol), {}, position + 1}
			: invalid;
	};
};

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

Parser operator!(const Parser& parser) {
	return [=] (const std::string& text, const size_t& position) -> Result {
		const auto result = parser(text, position);
		return result.valid ? result : Result{true, "", {}, position};
	};
}

Parser operator-(const Parser& parser1, const Parser& parser2) {
	return [=] (const std::string& text, const size_t& position) -> Result {
		const auto result1 = parser1(text, position);
		return result1.valid && !parser2(text, position).valid
			? result1
			: invalid;
	};
}

Parser operator|(const Parser& parser1, const Parser& parser2) {
	return [=] (const std::string& text, const size_t& position) -> Result {
		const auto result1 = parser1(text, position);
		return result1.valid ? result1 : parser2(text, position);
	};
}

Parser operator,(const Parser& parser1, const Parser& parser2) {
	return [=] (const std::string& text, const size_t& position) -> Result {
		const auto result1 = parser1(text, position);
		if (!result1.valid) {
			return invalid;
		}

		const auto result2 = parser2(text, result1.position);
		if (!result2.valid) {
			return invalid;
		}

		return Result{true, "", {result1, result2}, result2.position};
	};
}

int main(void) try {
	const auto text = "12";
	const auto parser = (symbol('1'), symbol('2'));
	std::cout << parser(text, 0) << std::endl;
} catch (std::exception& exception) {
	std::cerr << "Error: \"" << exception.what() << "\"." << std::endl;
}
