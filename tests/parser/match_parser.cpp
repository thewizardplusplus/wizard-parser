#include "../../source/thewizardplusplus/wizard_parser/parser/match_parser.hpp"
#include "../../source/thewizardplusplus/wizard_parser/lexer/token.hpp"
#include "../../source/thewizardplusplus/wizard_parser/parser/rule_parser.hpp"
#include "../../source/thewizardplusplus/wizard_parser/parser/ast_node.hpp"
#include "../vendor/catch/catch.hpp"

TEST_CASE("parser::match_parser class", "[parser]") {
	using namespace thewizardplusplus::wizard_parser;
	using namespace thewizardplusplus::wizard_parser::parser::operators;

	const auto match_parser = "test"_t;
	auto tokens = lexer::token_group{{"one", "two", 1}, {"three", "four", 4}};
	const auto match = parser::parsing_result{
		parser::ast_node{
			tokens.front().type,
			tokens.front().value,
			{},
			tokens.front().offset
		},
		lexer::token_span{tokens}.subspan(1)
	};

	SECTION("not match without tokens") {
		const auto [ast, rest_tokens] = match_parser->parse({});
		CHECK(!ast.has_value());
		CHECK(rest_tokens.empty());
	}

	SECTION("not match with tokens") {
		const auto [ast, rest_tokens] = match_parser->parse(tokens);
		CHECK(!ast.has_value());
		CHECK(rest_tokens == lexer::token_span{tokens});
	}

	SECTION("match by a type") {
		const auto [ast, rest_tokens] = "one"_t->parse(tokens);
		REQUIRE(ast.has_value());
		CHECK(*ast == *match.node);
		CHECK(rest_tokens == match.rest_tokens);
	}

	SECTION("match by a value") {
		const auto [ast, rest_tokens] = "two"_v->parse(tokens);
		REQUIRE(ast.has_value());
		CHECK(*ast == *match.node);
		CHECK(rest_tokens == match.rest_tokens);
	}
}
