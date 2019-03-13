#define THEWIZARDPLUSPLUS_WIZARD_PARSER_PARSER_MACROSES

#include "../common/common.hpp"
#include "../../source/thewizardplusplus/wizard_parser/lexer/token.hpp"
#include "../../source/thewizardplusplus/wizard_parser/parser/rule_parser.hpp"
#include "../../source/thewizardplusplus/wizard_parser/parser/typing_parser.hpp"
#include "../../source/thewizardplusplus/wizard_parser/parser/ast_node.hpp"
#include "../vendor/catch/catch.hpp"
#include "../vendor/fakeit/fakeit.hpp"

TEST_CASE("parser::typing_parser class", "[parser]") {
	using namespace thewizardplusplus::wizard_parser;
	using namespace tests::common;

	auto tokens = lexer::token_group{{"one", "two", 1}, {"three", "four", 4}};

	SECTION("without a match") {
		auto mock_parser = fakeit::Mock<parser::rule_parser>{};
		fakeit::When(Method(mock_parser, parse))
			.Return(parser::parsing_result{{}, tokens});
		fakeit::Fake(Dtor(mock_parser));

		RULE(typing_parser) = parser::rule_parser::pointer{&mock_parser.get()};
		const auto [ast, rest_tokens] = typing_parser->parse(tokens);
		CHECK(!ast.has_value());
		CHECK(rest_tokens == lexer::token_span{tokens});

		fakeit::Verify(Method(mock_parser, parse)).Once();
	}

	SECTION("with a match") {
		const auto match = parser::parsing_result{
			parser::ast_node{
				tokens.front().type,
				tokens.front().value,
				{},
				tokens.front().offset
			},
			lexer::token_span{tokens}.subspan(1)
		};
		auto mock_parser = fakeit::Mock<parser::rule_parser>{};
		fakeit::When(Method(mock_parser, parse)).Return(match);
		fakeit::Fake(Dtor(mock_parser));

		const auto expected_match = ast_with_type(match, "typing_parser");
		RULE(typing_parser) = parser::rule_parser::pointer{&mock_parser.get()};
		const auto [ast, rest_tokens] = typing_parser->parse(tokens);
		REQUIRE(ast.has_value());
		CHECK(*ast == *expected_match.node);
		CHECK(rest_tokens == expected_match.rest_tokens);

		fakeit::Verify(Method(mock_parser, parse)).Once();
	}
}
