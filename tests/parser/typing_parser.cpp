#define THEWIZARDPLUSPLUS_WIZARD_PARSER_PARSER_MACROSES

#include "../../source/thewizardplusplus/wizard_parser/parser/rule_parser.hpp"
#include "../../source/thewizardplusplus/wizard_parser/parser/typing_parser.hpp"
#include "../../source/thewizardplusplus/wizard_parser/lexer/token.hpp"
#include "../../source/thewizardplusplus/wizard_parser/parser/ast_node.hpp"
#include "../vendor/catch/catch.hpp"
#include "../vendor/fakeit/fakeit.hpp"

TEST_CASE("parser::typing_parser class", "[parser]") {
	using namespace thewizardplusplus::wizard_parser;

	SECTION("without tokens") {
		auto mock_parser = fakeit::Mock<parser::rule_parser>{};
		fakeit::When(Method(mock_parser, parse))
			.Return(parser::parsing_result{});
		fakeit::Fake(Dtor(mock_parser));

		RULE(typing_parser) = parser::rule_parser::pointer{&mock_parser.get()};
		const auto [ast, rest_tokens] = typing_parser->parse({});
		CHECK(!ast.has_value());
		CHECK(rest_tokens.empty());

		fakeit::Verify(Method(mock_parser, parse)).Once();
		fakeit::VerifyNoOtherInvocations(mock_parser);
	}

	SECTION("without a match") {
		auto tokens = lexer::token_group{{"one", "two", 1}, {"three", "four", 4}};
		auto mock_parser = fakeit::Mock<parser::rule_parser>{};
		fakeit::When(Method(mock_parser, parse))
			.Return(parser::parsing_result{{}, lexer::token_span{tokens}.subspan(1)});
		fakeit::Fake(Dtor(mock_parser));

		RULE(typing_parser) = parser::rule_parser::pointer{&mock_parser.get()};
		const auto [ast, rest_tokens] = typing_parser->parse(tokens);
		CHECK(!ast.has_value());
		CHECK(rest_tokens == lexer::token_span{tokens}.subspan(1));

		fakeit::Verify(Method(mock_parser, parse)).Once();
		fakeit::VerifyNoOtherInvocations(mock_parser);
	}

	SECTION("with a match") {
		auto tokens = lexer::token_group{{"one", "two", 1}, {"three", "four", 4}};
		auto mock_parser = fakeit::Mock<parser::rule_parser>{};
		fakeit::When(Method(mock_parser, parse))
			.Return(parser::parsing_result{
				parser::ast_node{"one", "two", {}, 1},
				lexer::token_span{tokens}.subspan(1)
			});
		fakeit::Fake(Dtor(mock_parser));

		RULE(typing_parser) = parser::rule_parser::pointer{&mock_parser.get()};
		const auto [ast, rest_tokens] = typing_parser->parse(tokens);
		REQUIRE(ast.has_value());
		CHECK(*ast == parser::ast_node{"typing_parser", {}, {{"one", "two", {}, 1}}});
		CHECK(rest_tokens == lexer::token_span{tokens}.subspan(1));

		fakeit::Verify(Method(mock_parser, parse)).Once();
		fakeit::VerifyNoOtherInvocations(mock_parser);
	}
}
