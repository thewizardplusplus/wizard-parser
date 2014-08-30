#ifndef PARSER_H
#define PARSER_H

#include "Result.h"
#include <functional>

using Parser = std::function<Result(const std::string&, const size_t&)>;

extern const Parser nothing;
extern const Parser end;

Parser operator"" _s(char symbol);
Parser operator"" _t(const char* text, size_t length);
Parser operator>>(const Parser& parser1, const Parser& parser2);
Parser operator|(const Parser& parser1, const Parser& parser2);
Parser operator!(const Parser& parser);
Parser operator*(const Parser& parser);
Parser operator-(const Parser& parser1, const Parser& parser2);

Parser hide(const Parser& parser);
Parser plain(const Parser& parser);
Parser lexeme(const Parser& parser);
Parser name(const std::string& name, const Parser& parser);
#endif
