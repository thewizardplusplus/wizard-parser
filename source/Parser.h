#ifndef PARSER_H
#define PARSER_H

#include "Result.h"
#include <functional>

using Parser = std::function<Result(const std::string&, const size_t&)>;

Parser operator"" _s(char symbol);
Parser operator"" _t(const char* text, size_t length);
Parser operator,(const Parser& parser1, const Parser& parser2);
Parser operator|(const Parser& parser1, const Parser& parser2);
Parser operator!(const Parser& parser);
Parser operator*(const Parser& parser);
Parser operator-(const Parser& parser1, const Parser& parser2);
Parser name(const std::string& name, const Parser& parser);
#endif
