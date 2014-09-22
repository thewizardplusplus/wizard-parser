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
	const auto text = "123.87,0.0,5,120,6.44";
	const auto parser = list(number(), ','_s);

	std::cout << parse(text, parser) << std::endl;
} catch (std::exception& exception) {
	std::cerr << "Error: \"" << exception.what() << "\"." << std::endl;
}
