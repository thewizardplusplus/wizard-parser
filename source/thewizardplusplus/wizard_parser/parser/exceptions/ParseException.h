#ifndef WIZARD_PARSER_PARSER_EXCEPTIONS_PARSE_EXCEPTION_HEADER
#define WIZARD_PARSER_PARSER_EXCEPTIONS_PARSE_EXCEPTION_HEADER

#include <stdexcept>

namespace thewizardplusplus {
namespace wizard_parser {
namespace parser {
namespace exceptions {

class ParseException : public std::runtime_error {
public:
	ParseException(const std::string& text, const size_t position);

private:
	static std::string formatDescription(
		const std::string& text,
		const size_t position
	);
};

}
}
}
}
#endif
