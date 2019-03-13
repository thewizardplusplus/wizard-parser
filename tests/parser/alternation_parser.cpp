#include "../../source/thewizardplusplus/wizard_parser/parser/rule_parser.hpp"
#include "../../source/thewizardplusplus/wizard_parser/parser/alternation_parser.hpp"
#include "../../source/thewizardplusplus/wizard_parser/lexer/token.hpp"
#include "../../source/thewizardplusplus/wizard_parser/parser/ast_node.hpp"
#include "../vendor/catch/catch.hpp"
#include "../vendor/fakeit/fakeit.hpp"

TEST_CASE("parser::alternation_parser class", "[parser]") {
	using namespace thewizardplusplus::wizard_parser;
	using namespace thewizardplusplus::wizard_parser::parser::operators;

	SECTION("without tokens") {
		auto left_mock_parser = fakeit::Mock<parser::rule_parser>{};
		fakeit::When(Method(left_mock_parser, parse))
			.Return(parser::parsing_result{});
		fakeit::Fake(Dtor(left_mock_parser));

		auto right_mock_parser = fakeit::Mock<parser::rule_parser>{};
		fakeit::When(Method(right_mock_parser, parse))
			.Return(parser::parsing_result{});
		fakeit::Fake(Dtor(right_mock_parser));

		const auto alternation_parser =
			parser::rule_parser::pointer{&left_mock_parser.get()}
			| parser::rule_parser::pointer{&right_mock_parser.get()};
		const auto [ast, rest_tokens] = alternation_parser->parse({});
		CHECK(!ast.has_value());
		CHECK(rest_tokens.empty());

		fakeit::Verify(Method(left_mock_parser, parse)).Once();
		fakeit::Verify(Method(right_mock_parser, parse)).Once();
	}

	SECTION("without matches") {
		auto tokens = lexer::token_group{{"one", "two", 1}, {"three", "four", 4}};
		auto left_mock_parser = fakeit::Mock<parser::rule_parser>{};
		fakeit::When(Method(left_mock_parser, parse))
			.Return(parser::parsing_result{{}, tokens});
		fakeit::Fake(Dtor(left_mock_parser));

		auto right_mock_parser = fakeit::Mock<parser::rule_parser>{};
		fakeit::When(Method(right_mock_parser, parse))
			.Return(parser::parsing_result{{}, tokens});
		fakeit::Fake(Dtor(right_mock_parser));

		const auto alternation_parser =
			parser::rule_parser::pointer{&left_mock_parser.get()}
			| parser::rule_parser::pointer{&right_mock_parser.get()};
		const auto [ast, rest_tokens] = alternation_parser->parse(tokens);
		CHECK(!ast.has_value());
		CHECK(rest_tokens == lexer::token_span{tokens});

		fakeit::Verify(Method(left_mock_parser, parse)).Once();
		fakeit::Verify(Method(right_mock_parser, parse)).Once();
	}

	SECTION("with a left match") {
		auto tokens = lexer::token_group{{"one", "two", 1}, {"three", "four", 4}};
		auto left_mock_parser = fakeit::Mock<parser::rule_parser>{};
		fakeit::When(Method(left_mock_parser, parse))
			.Return(parser::parsing_result{
				parser::ast_node{"one", "two", {}, 1},
				lexer::token_span{tokens}.subspan(1)
			});
		fakeit::Fake(Dtor(left_mock_parser));

		auto right_mock_parser = fakeit::Mock<parser::rule_parser>{};
		fakeit::When(Method(right_mock_parser, parse))
			.Return(parser::parsing_result{{}, tokens});
		fakeit::Fake(Dtor(right_mock_parser));

		const auto alternation_parser =
			parser::rule_parser::pointer{&left_mock_parser.get()}
			| parser::rule_parser::pointer{&right_mock_parser.get()};
		const auto [ast, rest_tokens] = alternation_parser->parse(tokens);
		REQUIRE(ast.has_value());
		CHECK(*ast == parser::ast_node{"one", "two", {}, 1});
		CHECK(rest_tokens == lexer::token_span{tokens}.subspan(1));

		fakeit::Verify(Method(left_mock_parser, parse)).Once();
		fakeit::Verify(Method(right_mock_parser, parse)).Once();
	}

	SECTION("with a right match") {
		auto tokens = lexer::token_group{{"one", "two", 1}, {"three", "four", 4}};
		auto left_mock_parser = fakeit::Mock<parser::rule_parser>{};
		fakeit::When(Method(left_mock_parser, parse))
			.Return(parser::parsing_result{{}, tokens});
		fakeit::Fake(Dtor(left_mock_parser));

		auto right_mock_parser = fakeit::Mock<parser::rule_parser>{};
		fakeit::When(Method(right_mock_parser, parse))
			.Return(parser::parsing_result{
				parser::ast_node{"one", "two", {}, 1},
				lexer::token_span{tokens}.subspan(1)
			});
		fakeit::Fake(Dtor(right_mock_parser));

		const auto alternation_parser =
			parser::rule_parser::pointer{&left_mock_parser.get()}
			| parser::rule_parser::pointer{&right_mock_parser.get()};
		const auto [ast, rest_tokens] = alternation_parser->parse(tokens);
		REQUIRE(ast.has_value());
		CHECK(*ast == parser::ast_node{"one", "two", {}, 1});
		CHECK(rest_tokens == lexer::token_span{tokens}.subspan(1));

		fakeit::Verify(Method(left_mock_parser, parse)).Once();
		fakeit::Verify(Method(right_mock_parser, parse)).Once();
	}

	SECTION("with left and right matches") {
		auto tokens = lexer::token_group{
			{"one", "two", 1},
			{"three", "four", 4},
			{"five", "six", 8}
		};
		auto left_mock_parser = fakeit::Mock<parser::rule_parser>{};
		fakeit::When(Method(left_mock_parser, parse))
			.Return(parser::parsing_result{
				parser::ast_node{"one", "two", {}, 1},
				lexer::token_span{tokens}.subspan(1)
			});
		fakeit::Fake(Dtor(left_mock_parser));

		auto right_mock_parser = fakeit::Mock<parser::rule_parser>{};
		fakeit::When(Method(right_mock_parser, parse))
			.Return(parser::parsing_result{
				parser::ast_node{"three", "four", {}, 4},
				lexer::token_span{tokens}.subspan(2)
			});
		fakeit::Fake(Dtor(right_mock_parser));

		const auto alternation_parser =
			parser::rule_parser::pointer{&left_mock_parser.get()}
			| parser::rule_parser::pointer{&right_mock_parser.get()};
		const auto [ast, rest_tokens] = alternation_parser->parse(tokens);
		REQUIRE(ast.has_value());
		CHECK(*ast == parser::ast_node{"one", "two", {}, 1});
		CHECK(rest_tokens == lexer::token_span{tokens}.subspan(1));

		fakeit::Verify(Method(left_mock_parser, parse)).Once();
		fakeit::Verify(Method(right_mock_parser, parse)).Once();
	}
}
