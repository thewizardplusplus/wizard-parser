#include "ParseException.h"
#include <algorithm>

using namespace thewizardplusplus::wizard_parser::parser::exceptions;

ParseException::ParseException(const std::string& text, const size_t position) :
	std::runtime_error(formatDescription(text, position))
{}

std::string ParseException::formatDescription(
	const std::string& text,
	const size_t position
) {
	const auto parsed_text = text.substr(0, position + 1);

	const auto line = std::count(parsed_text.begin(), parsed_text.end(), '\n');

	const auto last_line_index = parsed_text.rfind('\n');
	const auto parsed_text_length = parsed_text.length();
	const auto column =
		last_line_index != std::string::npos
			? parsed_text_length - last_line_index - 1
			: parsed_text_length;

	return
		"parse error on line "
		+ std::to_string(line)
		+ " and column "
		+ std::to_string(column);
}
