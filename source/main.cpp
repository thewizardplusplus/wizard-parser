#include "Parser.h"
#include <iostream>

const auto symbol = [] (const char& symbol) {
	return [=] (const std::string& text, const size_t& position) -> Result {
		return text.size() > position && text[position] == symbol
			? Result{true, std::string(1, symbol), {}, position + 1}
			: INVALID;
	};
};

int main(void) try {
	const auto text = "12";
	const auto parser = (symbol('1'), symbol('2'));
	std::cout << parser(text, 0) << std::endl;
} catch (std::exception& exception) {
	std::cerr << "Error: \"" << exception.what() << "\"." << std::endl;
}
