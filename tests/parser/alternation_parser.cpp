#include "../common/common.hpp"
#include "../../source/thewizardplusplus/wizard_parser/lexer/token.hpp"
#include "../../source/thewizardplusplus/wizard_parser/parser/rule_parser.hpp"
#include "../../source/thewizardplusplus/wizard_parser/parser/alternation_parser.hpp"
#include "../vendor/catch/catch.hpp"
#include "../vendor/fakeit/fakeit.hpp"

TEST_CASE("parser::alternation_parser class", "[parser]") {
	using namespace thewizardplusplus::wizard_parser;
	using namespace thewizardplusplus::wizard_parser::parser::operators;
	using namespace tests::common;

	auto tokens = lexer::token_group{{"one", "two", 1}, {"three", "four", 4}};
	const auto match = ast_from_token(tokens);

	SECTION("without matches") {
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
		auto left_mock_parser = fakeit::Mock<parser::rule_parser>{};
		fakeit::When(Method(left_mock_parser, parse)).Return(match);
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
		CHECK(*ast == *match.node);
		CHECK(rest_tokens == match.rest_tokens);

		fakeit::Verify(Method(left_mock_parser, parse)).Once();
		fakeit::Verify(Method(right_mock_parser, parse)).Once();
	}

	SECTION("with a right match") {
		auto left_mock_parser = fakeit::Mock<parser::rule_parser>{};
		fakeit::When(Method(left_mock_parser, parse))
			.Return(parser::parsing_result{{}, tokens});
		fakeit::Fake(Dtor(left_mock_parser));

		auto right_mock_parser = fakeit::Mock<parser::rule_parser>{};
		fakeit::When(Method(right_mock_parser, parse)).Return(match);
		fakeit::Fake(Dtor(right_mock_parser));

		const auto alternation_parser =
			parser::rule_parser::pointer{&left_mock_parser.get()}
			| parser::rule_parser::pointer{&right_mock_parser.get()};
		const auto [ast, rest_tokens] = alternation_parser->parse(tokens);
		REQUIRE(ast.has_value());
		CHECK(*ast == *match.node);
		CHECK(rest_tokens == match.rest_tokens);

		fakeit::Verify(Method(left_mock_parser, parse)).Once();
		fakeit::Verify(Method(right_mock_parser, parse)).Once();
	}

	SECTION("with left and right matches") {
		const auto left_ast = ast_with_type(match, "five");
		auto left_mock_parser = fakeit::Mock<parser::rule_parser>{};
		fakeit::When(Method(left_mock_parser, parse)).Return(left_ast);
		fakeit::Fake(Dtor(left_mock_parser));

		auto right_mock_parser = fakeit::Mock<parser::rule_parser>{};
		fakeit::When(Method(right_mock_parser, parse))
			.Return(ast_with_type(match, "six"));
		fakeit::Fake(Dtor(right_mock_parser));

		const auto alternation_parser =
			parser::rule_parser::pointer{&left_mock_parser.get()}
			| parser::rule_parser::pointer{&right_mock_parser.get()};
		const auto [ast, rest_tokens] = alternation_parser->parse(tokens);
		REQUIRE(ast.has_value());
		CHECK(*ast == *left_ast.node);
		CHECK(rest_tokens == left_ast.rest_tokens);

		fakeit::Verify(Method(left_mock_parser, parse)).Once();
		fakeit::Verify(Method(right_mock_parser, parse)).Once();
	}
}
