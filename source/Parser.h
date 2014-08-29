#ifndef PARSER_H
#define PARSER_H

#include "Result.h"
#include <functional>

using Parser = std::function<Result(const std::string&, const size_t&)>;

Parser operator,(const Parser& parser1, const Parser& parser2);
Parser operator*(const Parser& parser);
Parser operator+(const Parser& parser);
Parser operator|(const Parser& parser1, const Parser& parser2);
Parser operator!(const Parser& parser);
Parser operator-(const Parser& parser1, const Parser& parser2);
Parser list(const Parser& parser, const Parser& separator);
#endif
