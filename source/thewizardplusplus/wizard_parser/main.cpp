#include "Parser.h"
#include <iostream>

using namespace thewizardplusplus::wizard_parser;

Parser digit(void) {
	return some("0123456789");
}

Parser letter(void) {
	return some("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");
}

Parser number(void) {
	return lexeme(+digit() >> !('.'_s >> +digit()));
}

Parser identify(void) {
	return lexeme((letter() | '_'_s) >> *(letter() | '_'_s | digit()));
}

int main(void) try {
	const auto text = "ololo_,_,_34,_ololo445";
	const auto parser = list(identify(), ','_s);

	std::cout << parse(text, parser) << std::endl;
} catch (std::exception& exception) {
	std::cerr << "Error: \"" << exception.what() << "\"." << std::endl;
}
