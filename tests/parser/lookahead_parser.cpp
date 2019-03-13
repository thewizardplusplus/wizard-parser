#include "../../source/thewizardplusplus/wizard_parser/parser/ast_node.hpp"
#include "../../source/thewizardplusplus/wizard_parser/lexer/token.hpp"
#include "../../source/thewizardplusplus/wizard_parser/parser/rule_parser.hpp"
#include "../../source/thewizardplusplus/wizard_parser/parser/lookahead_parser.hpp"
#include "../vendor/catch/catch.hpp"
#include "../vendor/fakeit/fakeit.hpp"

TEST_CASE("parser::lookahead_parser class", "[parser]") {
	using namespace thewizardplusplus::wizard_parser;
	using namespace thewizardplusplus::wizard_parser::parser::operators;

	const auto type = (+parser::ast_node_type::nothing)._to_string();
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

	SECTION("positive lookahead without a match") {
		auto mock_parser = fakeit::Mock<parser::rule_parser>{};
		fakeit::When(Method(mock_parser, parse))
			.Return(parser::parsing_result{{}, tokens});
		fakeit::Fake(Dtor(mock_parser));

		const auto lookahead_parser =
			&parser::rule_parser::pointer{&mock_parser.get()};
		const auto [ast, rest_tokens] = lookahead_parser->parse(tokens);
		CHECK(!ast.has_value());
		CHECK(rest_tokens == lexer::token_span{tokens});

		fakeit::Verify(Method(mock_parser, parse)).Once();
	}

	SECTION("positive lookahead with a match") {
		auto mock_parser = fakeit::Mock<parser::rule_parser>{};
		fakeit::When(Method(mock_parser, parse)).Return(match);
		fakeit::Fake(Dtor(mock_parser));

		const auto lookahead_parser =
			&parser::rule_parser::pointer{&mock_parser.get()};
		const auto [ast, rest_tokens] = lookahead_parser->parse(tokens);
		REQUIRE(ast.has_value());
		CHECK(*ast == parser::ast_node{type, {}, {}, match.node->offset});
		CHECK(rest_tokens == match.rest_tokens);

		fakeit::Verify(Method(mock_parser, parse)).Once();
	}

	SECTION("negative lookahead without a match") {
		auto mock_parser = fakeit::Mock<parser::rule_parser>{};
		fakeit::When(Method(mock_parser, parse))
			.Return(parser::parsing_result{{}, tokens});
		fakeit::Fake(Dtor(mock_parser));

		const auto lookahead_parser =
			!parser::rule_parser::pointer{&mock_parser.get()};
		const auto [ast, rest_tokens] = lookahead_parser->parse(tokens);
		REQUIRE(ast.has_value());
		CHECK(*ast == parser::ast_node{type, {}, {}, lexer::get_offset(tokens)});
		CHECK(rest_tokens == lexer::token_span{tokens});

		fakeit::Verify(Method(mock_parser, parse)).Once();
	}

	SECTION("negative lookahead with a match") {
		auto mock_parser = fakeit::Mock<parser::rule_parser>{};
		fakeit::When(Method(mock_parser, parse)).Return(match);
		fakeit::Fake(Dtor(mock_parser));

		const auto lookahead_parser =
			!parser::rule_parser::pointer{&mock_parser.get()};
		const auto [ast, rest_tokens] = lookahead_parser->parse(tokens);
		CHECK(!ast.has_value());
		CHECK(rest_tokens == match.rest_tokens);

		fakeit::Verify(Method(mock_parser, parse)).Once();
	}
}
