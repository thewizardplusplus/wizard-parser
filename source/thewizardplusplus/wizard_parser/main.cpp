#include "Parser.h"
#include <iostream>

using namespace thewizardplusplus::wizard_parser;

Parser digit(void) {
	return
		'0'_s
		| '1'_s
		| '2'_s
		| '3'_s
		| '4'_s
		| '5'_s
		| '6'_s
		| '7'_s
		| '8'_s
		| '9'_s;
}

Parser number(void) {
	return lexeme(+digit() >> !('.'_s >> +digit()));
}

int main(void) try {
	const auto text = "123.87";
	const auto parser = number();

	const auto result = parser(text, 0);
	if (std::get<0>(result)) {
		std::cout << std::get<1>(parser(text, 0)) << std::endl;
	} else {
		throw std::runtime_error("parse error");
	}
} catch (std::exception& exception) {
	std::cerr << "Error: \"" << exception.what() << "\"." << std::endl;
}
