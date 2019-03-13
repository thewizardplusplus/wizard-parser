#include "../../source/thewizardplusplus/wizard_parser/parser/match_parser.hpp"
#include "../../source/thewizardplusplus/wizard_parser/lexer/token.hpp"
#include "../../source/thewizardplusplus/wizard_parser/parser/ast_node.hpp"
#include "../vendor/catch/catch.hpp"

TEST_CASE("parser::match_parser class", "[parser]") {
	using namespace thewizardplusplus::wizard_parser;
	using namespace thewizardplusplus::wizard_parser::parser::operators;

	SECTION("without tokens") {
		const auto [ast, rest_tokens] = "test"_t->parse({});
		CHECK(!ast.has_value());
		CHECK(rest_tokens.empty());
	}

	SECTION("without a match") {
		auto tokens = lexer::token_group{{"one", "two", 1}, {"three", "four", 4}};
		const auto [ast, rest_tokens] = "test"_t->parse(tokens);
		CHECK(!ast.has_value());
		CHECK(rest_tokens == lexer::token_span{tokens});
	}

	SECTION("with a match by a type") {
		auto tokens = lexer::token_group{{"one", "two", 1}, {"three", "four", 4}};
		const auto [ast, rest_tokens] = "one"_t->parse(tokens);
		REQUIRE(ast.has_value());
		CHECK(*ast == parser::ast_node{"one", "two", {}, 1});
		CHECK(rest_tokens == lexer::token_span{tokens}.subspan(1));
	}

	SECTION("with a match by a value") {
		auto tokens = lexer::token_group{{"one", "two", 1}, {"three", "four", 4}};
		const auto [ast, rest_tokens] = "two"_v->parse(tokens);
		REQUIRE(ast.has_value());
		CHECK(*ast == parser::ast_node{"one", "two", {}, 1});
		CHECK(rest_tokens == lexer::token_span{tokens}.subspan(1));
	}
}
