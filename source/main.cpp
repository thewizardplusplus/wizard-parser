#include "parser/Parser.h"
#include <iostream>

using namespace parser;

int main(void) try {
	const auto text = "123";
	const auto parser = "123"_t;
	const auto result = parser(text, 0);
	if (std::get<0>(result)) {
		std::cout << std::get<1>(parser(text, 0)) << std::endl;
	} else {
		throw std::runtime_error("parse error");
	}
} catch (std::exception& exception) {
	std::cerr << "Error: \"" << exception.what() << "\"." << std::endl;
}
