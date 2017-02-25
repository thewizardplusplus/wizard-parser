#include "vendor/docopt/docopt.hpp"
#include <thewizardplusplus/wizard_parser/lexer/lexeme.hpp>
#include <thewizardplusplus/wizard_parser/parser/parsers.hpp>
#include <thewizardplusplus/wizard_parser/parser/macroses.hpp>
#include <thewizardplusplus/wizard_parser/lexer/tokenize.hpp>
#include <thewizardplusplus/wizard_parser/parser/parse.hpp>
#include <regex>
#include <vector>
#include <string>
#include <unordered_set>
#include <iostream>
#include <iterator>
#include <cstdlib>
#include <exception>

using namespace thewizardplusplus::wizard_parser::lexer;
using namespace thewizardplusplus::wizard_parser::parser;
using namespace thewizardplusplus::wizard_parser::parser::operators;

const auto usage =
R"(Usage:
  ./example -h | --help
  ./example [-t | --tokens] <expression>
  ./example [-t | --tokens] (-s | --stdin)

Options:
  -h, --help    - show this message;
  -t, --tokens  - show a token list instead an AST;
  -s, --stdin   - read an expression from stdin.)";
const auto lexemes = std::vector<lexeme>{
	{std::regex{"=="}, "equal"},
	{std::regex{"/="}, "not_equal"},
	{std::regex{"<"}, "less"},
	{std::regex{"<="}, "less_or_equal"},
	{std::regex{">"}, "great"},
	{std::regex{">="}, "great_or_equal"},
	{std::regex{R"(\+)"}, "plus"},
	{std::regex{"-"}, "minus"},
	{std::regex{R"(\*)"}, "star"},
	{std::regex{"/"}, "slash"},
	{std::regex{"%"}, "percent"},
	{std::regex{R"(\()"}, "opening_parenthesis"},
	{std::regex{R"(\))"}, "closing_parenthesis"},
	{std::regex{","}, "comma"},
	{std::regex{R"(\d+(?:\.\d+)?(?:e-?\d+)?)"}, "number_constant"},
	{std::regex{R"([A-Za-z_]\w*)"}, "base_identifier"},
	{std::regex{R"(\s+)"}, "whitespace"}
};
const auto ignorable_tokens = std::unordered_set<std::string>{"whitespace"};

namespace {

rule_parser::pointer make_atom_parser(const rule_parser::pointer& expression) {
	RULE(number_constant) = "number_constant"_t;
	RULE(key_words) = "and"_v | "not"_v | "or"_v;
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
	const auto expression_dummy = dummy();
	RULE(atom) = make_atom_parser(expression_dummy);
	RULE(unary) = *("-"_v | "not"_v) >> atom;
	RULE(product) = unary >> *(("*"_v | "/"_v | "%"_v) >> unary);
	RULE(sum) = product >> *(("+"_v | "-"_v) >> product);
	RULE(comparison) = sum >> *(("<"_v | "<="_v | ">"_v | ">="_v) >> sum);
	RULE(equality) = comparison >> *(("=="_v | "/="_v) >> comparison);
	RULE(conjunction) = equality >> *(&"and"_v >> equality);
	RULE(disjunction) = conjunction >> *(&"or"_v >> conjunction);
	expression_dummy->set_parser(disjunction);

	return disjunction >> eoi();
}

}

int main(int argc, char* argv[]) try {
	auto code = std::string{};
	const auto options = docopt::docopt(usage, {argv + 1, argv + argc}, true);
	if (!options.at("--stdin").asBool()) {
		code = options.at("<expression>").asString();
	} else {
		code = std::string{std::istreambuf_iterator<char>{std::cin}, {}};
	}

	const auto tokens = tokenize(lexemes, ignorable_tokens, code);
	if (options.at("--tokens").asBool()) {
		std::cout << tokens << '\n';
		std::exit(EXIT_SUCCESS);
	}

	RULE(expression) = make_expression_parser();
	const auto ast = parse(expression, tokens, code.size());
	std::cout << ast << '\n';
} catch (const std::exception& exception) {
	std::cerr << "error: " << exception.what() << '\n';
	std::exit(EXIT_FAILURE);
}
