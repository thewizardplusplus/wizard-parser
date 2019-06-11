#include "../../source/thewizardplusplus/wizard_parser/parser/rule_parser.hpp"
#include "../../source/thewizardplusplus/wizard_parser/parser/lookahead_parser.hpp"
#include "../../source/thewizardplusplus/wizard_parser/lexer/token.hpp"
#include "../../source/thewizardplusplus/wizard_parser/parser/ast_node.hpp"
#include "../../source/thewizardplusplus/wizard_parser/utilities/utilities.hpp"
#include "../vendor/catch/catch.hpp"
#include "../vendor/fakeit/fakeit.hpp"

TEST_CASE("parser::lookahead_parser class", "[parser]") {
	using namespace thewizardplusplus::wizard_parser;
	using namespace thewizardplusplus::wizard_parser::parser::operators;

	SECTION("positive lookahead without tokens") {
		auto mock_parser = fakeit::Mock<parser::rule_parser>{};
		fakeit::When(Method(mock_parser, parse))
			.Return(parser::parsing_result{});
		fakeit::Fake(Dtor(mock_parser));

		const auto lookahead_parser =
			&parser::rule_parser::pointer{&mock_parser.get()};
		const auto [ast, rest_tokens] = lookahead_parser->parse({});
		CHECK(!ast.has_value());
		CHECK(rest_tokens.empty());

		fakeit::Verify(Method(mock_parser, parse)).Once();
		fakeit::VerifyNoOtherInvocations(mock_parser);
	}

	SECTION("positive lookahead without a match") {
		auto tokens = lexer::token_group{{"one", "two", 1}, {"three", "four", 4}};
		auto mock_parser = fakeit::Mock<parser::rule_parser>{};
		fakeit::When(Method(mock_parser, parse))
			.Return(parser::parsing_result{{}, lexer::token_span{tokens}.subspan(1)});
		fakeit::Fake(Dtor(mock_parser));

		const auto lookahead_parser =
			&parser::rule_parser::pointer{&mock_parser.get()};
		const auto [ast, rest_tokens] = lookahead_parser->parse(tokens);
		CHECK(!ast.has_value());
		CHECK(rest_tokens == lexer::token_span{tokens}.subspan(1));

		fakeit::Verify(Method(mock_parser, parse)).Once();
		fakeit::VerifyNoOtherInvocations(mock_parser);
	}

	SECTION("positive lookahead with a match") {
		const auto type = (+parser::ast_node_type::nothing)._to_string();
		auto tokens = lexer::token_group{{"one", "two", 1}, {"three", "four", 4}};
		auto mock_parser = fakeit::Mock<parser::rule_parser>{};
		fakeit::When(Method(mock_parser, parse))
			.Return(parser::parsing_result{
				parser::ast_node{"one", "two", {}, 1},
				lexer::token_span{tokens}.subspan(1)
			});
		fakeit::Fake(Dtor(mock_parser));

		const auto lookahead_parser =
			&parser::rule_parser::pointer{&mock_parser.get()};
		const auto [ast, rest_tokens] = lookahead_parser->parse(tokens);
		REQUIRE(ast.has_value());
		CHECK(*ast == parser::ast_node{type, {}, {}, 1});
		CHECK(rest_tokens == lexer::token_span{tokens}.subspan(1));

		fakeit::Verify(Method(mock_parser, parse)).Once();
		fakeit::VerifyNoOtherInvocations(mock_parser);
	}

	SECTION("negative lookahead without tokens") {
		const auto type = (+parser::ast_node_type::nothing)._to_string();
		auto mock_parser = fakeit::Mock<parser::rule_parser>{};
		fakeit::When(Method(mock_parser, parse))
			.Return(parser::parsing_result{});
		fakeit::Fake(Dtor(mock_parser));

		const auto lookahead_parser =
			!parser::rule_parser::pointer{&mock_parser.get()};
		const auto [ast, rest_tokens] = lookahead_parser->parse({});
		REQUIRE(ast.has_value());
		CHECK(*ast == parser::ast_node{type, {}, {}, utilities::integral_infinity});
		CHECK(rest_tokens.empty());

		fakeit::Verify(Method(mock_parser, parse)).Once();
		fakeit::VerifyNoOtherInvocations(mock_parser);
	}

	SECTION("negative lookahead without a match") {
		const auto type = (+parser::ast_node_type::nothing)._to_string();
		auto tokens = lexer::token_group{{"one", "two", 1}, {"three", "four", 4}};
		auto mock_parser = fakeit::Mock<parser::rule_parser>{};
		fakeit::When(Method(mock_parser, parse))
			.Return(parser::parsing_result{{}, lexer::token_span{tokens}.subspan(1)});
		fakeit::Fake(Dtor(mock_parser));

		const auto lookahead_parser =
			!parser::rule_parser::pointer{&mock_parser.get()};
		const auto [ast, rest_tokens] = lookahead_parser->parse(tokens);
		REQUIRE(ast.has_value());
		CHECK(*ast == parser::ast_node{type, {}, {}, 1});
		CHECK(rest_tokens == lexer::token_span{tokens});

		fakeit::Verify(Method(mock_parser, parse)).Once();
		fakeit::VerifyNoOtherInvocations(mock_parser);
	}

	SECTION("negative lookahead with a match") {
		auto tokens = lexer::token_group{{"one", "two", 1}, {"three", "four", 4}};
		auto mock_parser = fakeit::Mock<parser::rule_parser>{};
		fakeit::When(Method(mock_parser, parse))
			.Return(parser::parsing_result{
				parser::ast_node{"one", "two", {}, 1},
				lexer::token_span{tokens}.subspan(1)
			});
		fakeit::Fake(Dtor(mock_parser));

		const auto lookahead_parser =
			!parser::rule_parser::pointer{&mock_parser.get()};
		const auto [ast, rest_tokens] = lookahead_parser->parse(tokens);
		CHECK(!ast.has_value());
		CHECK(rest_tokens == lexer::token_span{tokens});

		fakeit::Verify(Method(mock_parser, parse)).Once();
		fakeit::VerifyNoOtherInvocations(mock_parser);
	}
}
