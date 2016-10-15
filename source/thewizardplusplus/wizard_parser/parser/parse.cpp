#include "parse.hpp"
#include "value_match_parser.hpp"
#include "alternation_parser.hpp"
#include "utilities.hpp"
#include "rule_parser.hpp"
#include "type_match_parser.hpp"
#include "exception_parser.hpp"
#include "hide_parser.hpp"
#include "repetition_parser.hpp"
#include "concatenation_parser.hpp"
#include "optional_parser.hpp"
#include "dummy_parser.hpp"
#include "eoi_parser.hpp"
#include <memory>
#include <iterator>
#include <sstream>
#include <stdexcept>

using namespace parser;
using namespace lexer;

RULE(key_words) = "and"_v | "not"_v | "or"_v;

namespace {

rule_parser::pointer make_atom_parser(const rule_parser::pointer& expression) {
	RULE(number_constant) = "number_constant"_t;
	RULE(identifier) = "base_identifier"_t - key_words;
	IMPORTANT_RULE(function_call) = identifier >> &"("_v >>
		-(expression >> *(&","_v >> expression))
	>> &")"_v;
	return number_constant
		| identifier
		| function_call
		| (&"("_v >> expression >> &")"_v);
}

rule_parser::pointer make_expression_parser() {
	const auto expression_dummy = std::make_shared<dummy_parser>();
	RULE(atom) = make_atom_parser(expression_dummy);
	RULE(unary) = *("-"_v | "not"_v) >> atom;
	RULE(product) = unary >> *(("*"_v | "/"_v | "%"_v) >> unary);
	RULE(sum) = product >> *(("+"_v | "-"_v) >> product);
	RULE(comparison) = sum >> *(("<"_v | "<="_v | ">"_v | ">="_v) >> sum);
	RULE(equality) = comparison >> *(("=="_v | "/="_v) >> comparison);
	RULE(conjunction) = equality >> *(&"and"_v >> equality);
	RULE(disjunction) = conjunction >> *(&"or"_v >> conjunction);
	expression_dummy->set_parser(disjunction);

	RULE(eoi) = std::make_shared<eoi_parser>();
	return disjunction >> eoi;
}

}

namespace parser {

ast_node parse(token_group&& tokens) {
	RULE(expression) = make_expression_parser();
	const auto ast = expression->parse(std::cbegin(tokens), std::cend(tokens));
	if (!ast.is_parsed) {
		if (ast.last_token != std::cend(tokens)) {
			auto out = std::ostringstream{};
			out << *ast.last_token;

			throw std::runtime_error{"the unexpected token " + out.str()};
		} else {
			throw std::runtime_error{"the unexpected EOI"};
		}
	}

	return ast.node;
}

}
