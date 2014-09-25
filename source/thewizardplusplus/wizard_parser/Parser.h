#ifndef PARSER_H
#define PARSER_H

#include "Result.h"
#include <functional>
#include <memory>

namespace thewizardplusplus {
namespace wizard_parser {

using ParserFunction = std::function<Result(const std::string&, const size_t)>;
using Parser = std::shared_ptr<ParserFunction>;

void set_separator_parser(const Parser& parser);
Parser separate(const Parser& parser, bool separate);
Parser hide(const Parser& parser);
Parser name(const std::string& name, const Parser& parser);
Parser plain(const Parser& parser, const size_t level = -1);
Parser lexeme(const Parser& parser);

Parser operator>>(const Parser& parser1, const Parser& parser2);
Parser operator|(const Parser& parser1, const Parser& parser2);
Parser operator!(const Parser& parser);
Parser operator*(const Parser& parser);
Parser operator+(const Parser& parser);
Parser operator-(const Parser& parser1, const Parser& parser2);
Parser list(const Parser& parser, const Parser& separator);

Parser nothing(void);
Parser boundary(void);
Parser end(void);
Parser separator(void);

Parser operator"" _s(const char symbol);
Parser operator"" _t(const char* text, const size_t length);
Parser any(const std::string& symbols);
Parser any(void);
Parser space(void);
Parser letter(void);
Parser digit(void);
Parser word(void);
Parser word(const Parser& parser);

Node parse(const Parser& parser, const std::string& text);

}
}
#endif
