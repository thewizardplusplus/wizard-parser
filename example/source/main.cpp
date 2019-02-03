#define THEWIZARDPLUSPLUS_WIZARD_PARSER_PARSER_MACROSES

#include "vendor/better-enums/enum_strict.hpp"
#include "vendor/fmt/format.hpp"
#include "vendor/json.hpp"
#include "vendor/range/v3/view/transform.hpp"
#include "vendor/docopt/docopt.hpp"
#include "vendor/range/v3/view/filter.hpp"
#include "vendor/range/v3/to_container.hpp"
#include <thewizardplusplus/wizard_parser/lexer/lexeme.hpp>
#include <thewizardplusplus/wizard_parser/lexer/token.hpp>
#include <thewizardplusplus/wizard_parser/parser/ast_node.hpp>
#include <thewizardplusplus/wizard_parser/parser/rule_parser.hpp>
#include <thewizardplusplus/wizard_parser/parser/dummy_parser.hpp>
#include <thewizardplusplus/wizard_parser/parser/typing_parser.hpp>
#include <thewizardplusplus/wizard_parser/parser/match_parser.hpp>
#include <thewizardplusplus/wizard_parser/parser/alternation_parser.hpp>
#include <thewizardplusplus/wizard_parser/parser/exception_parser.hpp>
#include <thewizardplusplus/wizard_parser/parser/concatenation_parser.hpp>
#include <thewizardplusplus/wizard_parser/parser/lookahead_parser.hpp>
#include <thewizardplusplus/wizard_parser/parser/repetition_parser.hpp>
#include <thewizardplusplus/wizard_parser/lexer/tokenize.hpp>
#include <thewizardplusplus/wizard_parser/utilities/utilities.hpp>
#include <regex>
#include <cstdint>
#include <stdexcept>
#include <cstddef>
#include <iostream>
#include <string>
#include <cstdlib>
#include <functional>
#include <iterator>
#include <exception>

using namespace thewizardplusplus::wizard_parser::lexer;
using namespace thewizardplusplus::wizard_parser::parser;
using namespace thewizardplusplus::wizard_parser::parser::operators;
using namespace thewizardplusplus::wizard_parser::utilities;

const auto usage =
R"(Usage:
  ./example -h | --help
  ./example [-t | --tokens] [--] <expression>
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

BETTER_ENUM(entity_type, std::uint8_t, symbol, token, eoi)

template<entity_type::_integral type>
struct unexpected_entity_exception final: std::runtime_error {
	static_assert(entity_type::_is_valid(type));

	explicit unexpected_entity_exception(const std::size_t& offset);
};

template<entity_type::_integral type>
unexpected_entity_exception<type>::unexpected_entity_exception(
	const std::size_t& offset
):
	std::runtime_error{fmt::format(
		"unexpected {:s} (offset: {:d})",
		entity_type::_from_integral(type)._to_string(),
		offset
	)}
{}

namespace thewizardplusplus::wizard_parser::lexer {

void to_json(nlohmann::json& json, const token& some_token) {
	json = {
		{ "type", some_token.type },
		{ "value", some_token.value },
		{ "offset", some_token.offset }
	};
}

}

namespace thewizardplusplus::wizard_parser::parser {

void to_json(nlohmann::json& json, const ast_node& ast) {
	json = { { "type", ast.type } };
	if (!ast.value.empty()) {
		json["value"] = ast.value;
	}
	if (!ast.children.empty()) {
		json["children"] = ast.children;
	}
	if (ast.offset) {
		json["offset"] = *ast.offset;
	}
}

}

void stop(const int& code, std::ostream& stream, const std::string& message) {
	stream << fmt::format("{:s}\n", message);
	std::exit(code);
}

rule_parser::pointer make_parser() {
	const auto expression_dummy = dummy();
	RULE(key_words) = "not"_v | "and"_v | "or"_v;
	RULE(identifier) = "base_identifier"_t - key_words;
	RULE(function_call) = identifier >> &"("_v >>
		-(expression_dummy >> *(&","_v >> expression_dummy))
	>> &")"_v;
	RULE(atom) = "number"_t
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

	return disjunction;
}

ast_node walk_ast(
	const ast_node& ast,
	const std::function<ast_node(const ast_node&)>& handler
) {
	const auto new_ast = handler(ast);
	const auto new_children = new_ast.children
		| ranges::view::transform([&] (const auto& ast) {
			return walk_ast(ast, handler);
		});
	return {new_ast.type, new_ast.value, new_children, new_ast.offset};
}

int main(int argc, char* argv[]) try {
	const auto options = docopt::docopt(usage, {argv+1, argv+argc}, true);
	const auto code = options.at("--stdin").asBool()
		? std::string{std::istreambuf_iterator<char>{std::cin}, {}}
		: options.at("<expression>").asString();
	const auto [tokens, rest_offset] = tokenize(lexemes, code);
	if (rest_offset != code.size()) {
		throw unexpected_entity_exception<entity_type::symbol>{rest_offset};
	}

	auto cleaned_tokens = tokens
		| ranges::view::filter([] (const auto& token) {
			return token.type != "whitespace";
		})
		| ranges::to_<token_group>();
	if (options.at("--tokens").asBool()) {
		stop(EXIT_SUCCESS, std::cout, nlohmann::json(cleaned_tokens).dump());
	}

	const auto parser = make_parser();
	const auto ast = parser->parse(cleaned_tokens);
	if (!ast.rest_tokens.empty()) {
		throw unexpected_entity_exception<entity_type::token>{
			get_offset(ast.rest_tokens)
		};
	}
	if (!ast.node) {
		throw unexpected_entity_exception<entity_type::eoi>{code.size()};
	}

	const auto transformed_ast = walk_ast(*ast.node, [&] (const auto& ast) {
		const auto offset = ast.offset && *ast.offset == integral_infinity
			? code.size()
			: ast.offset;
		return ast_node{ast.type, ast.value, ast.children, offset};
	});
	stop(EXIT_SUCCESS, std::cout, nlohmann::json(transformed_ast).dump());
} catch (const std::exception& exception) {
	stop(EXIT_FAILURE, std::cerr, fmt::format("error: {:s}", exception.what()));
}
