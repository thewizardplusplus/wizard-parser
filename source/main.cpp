#include "Parser.h"
#include <iostream>

const auto symbol = [] (const char& symbol) {
	return [=] (const std::string& text, const size_t& position) -> Result {
		return text.size() > position && text[position] == symbol
			? Result{true, Node{std::string(1, symbol), {}}, position + 1}
			: INVALID;
	};
};

int main(void) try {
	const auto text = "12";
	const auto parser = (symbol('1'), symbol('2'));
	const auto result = parser(text, 0);
	if (std::get<0>(result)) {
		std::cout << std::get<1>(parser(text, 0)) << std::endl;
	} else {
		throw std::runtime_error("parse error");
	}
} catch (std::exception& exception) {
	std::cerr << "Error: \"" << exception.what() << "\"." << std::endl;
}
