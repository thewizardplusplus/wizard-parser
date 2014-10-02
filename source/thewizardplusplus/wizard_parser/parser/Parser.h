#ifndef WIZARD_PARSER_PARSER_PARSER_HEADER
#define WIZARD_PARSER_PARSER_PARSER_HEADER

#include "Result.h"
#include <functional>
#include <memory>

#ifndef WP_DISABLE_MACROSES
	#define WP_RULE(rule) const auto rule = name(#rule,
	#define WP_END );
#endif

namespace thewizardplusplus {
namespace wizard_parser {
namespace parser {

using ParserFunction = std::function<Result(const std::string&, const size_t)>;
using Parser = std::shared_ptr<ParserFunction>;
enum class SimplifyLevel : uint8_t {
	EMPTIES,
	WRAPPERS,
	AST
};
using StringGroup = std::vector<std::string>;

void assign(const Parser& parser1, const Parser& parser2);
Parser separation(const Parser& separator, const Parser& parser);
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
Parser separator(void);
Parser end(void);

Parser operator"" _s(const char symbol);
Parser operator"" _t(const char* text, const size_t length);
Parser any(void);
Parser any(const std::string& symbols);
Parser space(void);
Parser letter(void);
Parser digit(void);
Parser word(void);
Parser word(const Parser& parser);

node::Node simplify(
	const node::Node& node,
	const SimplifyLevel level = SimplifyLevel::WRAPPERS,
	const StringGroup& saved = {}
);
node::Node parse(
	const Parser& parser,
	const std::string& text,
	const SimplifyLevel level = SimplifyLevel::WRAPPERS,
	const StringGroup& saved = {}
);

}
}
}
#endif
