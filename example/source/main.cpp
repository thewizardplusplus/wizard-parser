#include "vendor/json.hpp"
#include "vendor/docopt/docopt.hpp"
#include "vendor/fmt/format.hpp"
#include <thewizardplusplus/wizard_parser/lexer/lexeme.hpp>
#include <thewizardplusplus/wizard_parser/lexer/token.hpp>
#include <thewizardplusplus/wizard_parser/parser/ast_node.hpp>
#include <thewizardplusplus/wizard_parser/parser/rule_parser.hpp>
#include <thewizardplusplus/wizard_parser/parser/dummy_parser.hpp>
#include <thewizardplusplus/wizard_parser/parser/macroses.hpp>
#include <thewizardplusplus/wizard_parser/parser/match_parser.hpp>
#include <thewizardplusplus/wizard_parser/parser/alternation_parser.hpp>
#include <thewizardplusplus/wizard_parser/parser/exception_parser.hpp>
#include <thewizardplusplus/wizard_parser/parser/concatenation_parser.hpp>
#include <thewizardplusplus/wizard_parser/parser/lookahead_parser.hpp>
#include <thewizardplusplus/wizard_parser/parser/repetition_parser.hpp>
#include <thewizardplusplus/wizard_parser/parser/eoi_parser.hpp>
#include <thewizardplusplus/wizard_parser/lexer/tokenize.hpp>
#include <thewizardplusplus/wizard_parser/parser/parse.hpp>
#include <thewizardplusplus/wizard_parser/exceptions/unexpected_entity_exception.hpp>
#include <regex>
#include <iostream>
#include <string>
#include <iterator>
#include <algorithm>
#include <cstdlib>
#include <exception>

using namespace thewizardplusplus::wizard_parser::lexer;
using namespace thewizardplusplus::wizard_parser::parser;
using namespace thewizardplusplus::wizard_parser::parser::operators;
using namespace thewizardplusplus::wizard_parser::exceptions;

const auto usage =
R"(Usage:
  ./example -h | --help
  ./example [-t | --tokens] <expression>
  ./example [-t | --tokens] (-s | --stdin)

Options:
  -h, --help    - show this message;
  -t, --tokens  - show a token list instead an AST;
  -s, --stdin   - read an expression from stdin.)";
const auto lexemes = lexeme_group{
	{std::regex{"=="}, "equal"},
	{std::regex{"/="}, "not_equal"},
	{std::regex{"<="}, "less_or_equal"},
	{std::regex{"<"}, "less"},
	{std::regex{">="}, "great_or_equal"},
	{std::regex{">"}, "great"},
	{std::regex{R"(\+)"}, "plus"},
	{std::regex{"-"}, "minus"},
	{std::regex{R"(\*)"}, "star"},
	{std::regex{"/"}, "slash"},
	{std::regex{"%"}, "percent"},
	{std::regex{R"(\()"}, "opening_parenthesis"},
	{std::regex{R"(\))"}, "closing_parenthesis"},
	{std::regex{","}, "comma"},
	{std::regex{R"(\d+(?:\.\d+)?(?:e-?\d+)?)"}, "number"},
	{std::regex{R"([A-Za-z_]\w*)"}, "base_identifier"},
	{std::regex{R"(\s+)"}, "whitespace"}
};

namespace thewizardplusplus::wizard_parser {

namespace lexer {

void to_json(nlohmann::json& json, const token& some_token) {
	json = { { "type", some_token.type }, { "value", some_token.value } };
}

}

namespace parser {

void to_json(nlohmann::json& json, const ast_node& ast) {
	json = { { "type", ast.type } };
	if (!ast.value.empty()) {
		json["value"] = ast.value;
	}
	if (!ast.children.empty()) {
		json["children"] = ast.children;
	}
}

}

}

void stop(const int& code, std::ostream& stream, const std::string& message) {
	stream << fmt::format("{:s}\n", message);
	std::exit(code);
}

rule_parser::pointer make_parser() {
	const auto expression_dummy = dummy();
	RULE(number) = "number"_t;
	RULE(key_words) = "not"_v | "and"_v | "or"_v;
	RULE(identifier) = "base_identifier"_t - key_words;
	RULE(function_call) = identifier >> &"("_v >>
		-(expression_dummy >> *(&","_v >> expression_dummy))
	>> &")"_v;
	RULE(atom) = number
		| function_call
		| identifier
		| (&"("_v >> expression_dummy >> &")"_v);
	RULE(unary) = *("-"_v | "not"_v) >> atom;
	RULE(product) = unary >> *(("*"_v | "/"_v | "%"_v) >> unary);
	RULE(sum) = product >> *(("+"_v | "-"_v) >> product);
	RULE(comparison) = sum >> *(("<"_v | "<="_v | ">"_v | ">="_v) >> sum);
	RULE(equality) = comparison >> *(("=="_v | "/="_v) >> comparison);
	RULE(conjunction) = equality >> *(&"and"_v >> equality);
	RULE(disjunction) = conjunction >> *(&"or"_v >> conjunction);
	expression_dummy->set_parser(disjunction);

	RULE(expression) = disjunction >> eoi();
	return expression;
}

int main(int argc, char* argv[]) try {
	auto cleaned_tokens = token_group{};
	const auto options = docopt::docopt(usage, {argv+1, argv+argc}, true);
	const auto code = options.at("--stdin").asBool()
		? std::string{std::istreambuf_iterator<char>{std::cin}, {}}
		: options.at("<expression>").asString();
	const auto tokens = tokenize(lexemes, code);
	std::copy_if(
		std::cbegin(tokens),
		std::cend(tokens),
		std::back_inserter(cleaned_tokens),
		[] (const auto& token) { return token.type != "whitespace"; }
	);
	if (options.at("--tokens").asBool()) {
		stop(EXIT_SUCCESS, std::cout, nlohmann::json(cleaned_tokens).dump());
	}

	const auto parser = make_parser();
	try {
		const auto ast = parse(parser, cleaned_tokens);
		stop(EXIT_SUCCESS, std::cout, nlohmann::json(ast).dump());
	} catch (const unexpected_entity_exception<entity_type::eoi>& exception) {
		throw decltype(exception){code.size()};
	}
} catch (const std::exception& exception) {
	stop(EXIT_FAILURE, std::cerr, fmt::format("error: {:s}", exception.what()));
}
