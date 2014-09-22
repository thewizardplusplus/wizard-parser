#ifndef PARSER_H
#define PARSER_H

#include "Result.h"
#include <functional>

namespace thewizardplusplus {
namespace wizard_parser {

using Parser = std::function<Result(const std::string&, const size_t)>;

Parser hide(const Parser& parser);
Parser name(const std::string& name, const Parser& parser);
Parser plain(const Parser& parser);
Parser lexeme(const Parser& parser);

Parser operator>>(const Parser& parser1, const Parser& parser2);
Parser operator|(const Parser& parser1, const Parser& parser2);
Parser operator!(const Parser& parser);
Parser operator*(const Parser& parser);
Parser operator+(const Parser& parser);
Parser operator-(const Parser& parser1, const Parser& parser2);

Parser nothing(void);
Parser end(void);
Parser operator"" _s(const char symbol);
Parser operator"" _t(const char* text, const size_t length);

}
}
#endif
