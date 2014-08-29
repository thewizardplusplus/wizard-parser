#include "Parser.h"
#include <iostream>

int main(void) try {
	const auto text = "1,1,1,1";
	const auto parser = name("list", plain(('1'_s, *(','_s, '1'_s))));
	const auto result = parser(text, 0);
	if (std::get<0>(result)) {
		std::cout << std::get<1>(parser(text, 0)) << std::endl;
	} else {
		throw std::runtime_error("parse error");
	}
} catch (std::exception& exception) {
	std::cerr << "Error: \"" << exception.what() << "\"." << std::endl;
}
