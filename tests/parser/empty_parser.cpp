#include "../../source/thewizardplusplus/wizard_parser/parser/ast_node.hpp"
#include "../../source/thewizardplusplus/wizard_parser/parser/empty_parser.hpp"
#include "../../source/thewizardplusplus/wizard_parser/utilities/utilities.hpp"
#include "../../source/thewizardplusplus/wizard_parser/lexer/token.hpp"
#include "../vendor/catch/catch.hpp"

TEST_CASE("parser::empty_parser class", "[parser]") {
	using namespace thewizardplusplus::wizard_parser;

	SECTION("without tokens") {
		const auto type = (+parser::ast_node_type::nothing)._to_string();
		const auto [ast, rest_tokens] = parser::empty()->parse({});
		REQUIRE(ast.has_value());
		CHECK(*ast == parser::ast_node{type, {}, {}, utilities::integral_infinity});
		CHECK(rest_tokens.empty());
	}

	SECTION("with tokens") {
		const auto type = (+parser::ast_node_type::nothing)._to_string();
		auto tokens = lexer::token_group{{"one", "two", 1}, {"three", "four", 4}};
		const auto [ast, rest_tokens] = parser::empty()->parse(tokens);
		REQUIRE(ast.has_value());
		CHECK(*ast == parser::ast_node{type, {}, {}, 1});
		CHECK(rest_tokens == lexer::token_span{tokens});
	}
}
