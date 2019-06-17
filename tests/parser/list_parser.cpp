#include "../../source/thewizardplusplus/wizard_parser/parser/rule_parser.hpp"
#include "../../source/thewizardplusplus/wizard_parser/parser/list_parser.hpp"
#include "../../source/thewizardplusplus/wizard_parser/lexer/token.hpp"
#include "../../source/thewizardplusplus/wizard_parser/parser/ast_node.hpp"
#include "../vendor/catch/catch.hpp"
#include "../vendor/fakeit/fakeit.hpp"

TEST_CASE("list parser", "[parser]") {
	using namespace thewizardplusplus::wizard_parser;
	using namespace thewizardplusplus::wizard_parser::parser::operators;
	using namespace fakeit;

	SECTION("without tokens") {
		auto general_parser = fakeit::Mock<parser::rule_parser>{};
		fakeit::When(Method(general_parser, parse))
			.Return(parser::parsing_result{});
		fakeit::Fake(Dtor(general_parser));

		auto separator_parser = fakeit::Mock<parser::rule_parser>{};
		fakeit::When(Method(separator_parser, parse))
			.Return(parser::parsing_result{});
		fakeit::Fake(Dtor(separator_parser));

		const auto list_parser =
			parser::rule_parser::pointer{&general_parser.get()}
			% parser::rule_parser::pointer{&separator_parser.get()};
		const auto [ast, rest_tokens] = list_parser->parse({});
		CHECK(!ast.has_value());
		CHECK(rest_tokens.empty());

		fakeit::Verify(Method(general_parser, parse)).Once();
		fakeit::VerifyNoOtherInvocations(general_parser);
		fakeit::VerifyNoOtherInvocations(separator_parser);
	}

	SECTION("without a match") {
		auto tokens = lexer::token_group{
			{"identifier", "one", 1},
			{"semicolon", ";", 4},
			{"two", "three", 5}
		};
		auto general_parser = fakeit::Mock<parser::rule_parser>{};
		fakeit::When(Method(general_parser, parse))
			.Return(parser::parsing_result{{}, lexer::token_span{tokens}.subspan(1)});
		fakeit::Fake(Dtor(general_parser));

		auto separator_parser = fakeit::Mock<parser::rule_parser>{};
		fakeit::When(Method(separator_parser, parse))
			.Return(parser::parsing_result{{}, lexer::token_span{tokens}.subspan(2)});
		fakeit::Fake(Dtor(separator_parser));

		const auto list_parser =
			parser::rule_parser::pointer{&general_parser.get()}
			% parser::rule_parser::pointer{&separator_parser.get()};
		const auto [ast, rest_tokens] = list_parser->parse(tokens);
		CHECK(!ast.has_value());
		CHECK(rest_tokens == lexer::token_span{tokens}.subspan(1));

		fakeit::Verify(Method(general_parser, parse)).Once();
		fakeit::VerifyNoOtherInvocations(general_parser);
		fakeit::VerifyNoOtherInvocations(separator_parser);
	}

	SECTION("with a match and without repetitions") {
		const auto type = (+parser::ast_node_type::sequence)._to_string();
		auto tokens = lexer::token_group{
			{"identifier", "one", 1},
			{"semicolon", ";", 4},
			{"two", "three", 5}
		};
		auto general_parser = fakeit::Mock<parser::rule_parser>{};
		fakeit::When(Method(general_parser, parse))
			.Return(parser::parsing_result{
				parser::ast_node{"identifier", "one", {}, 1},
				lexer::token_span{tokens}.subspan(1)
			});
		fakeit::Fake(Dtor(general_parser));

		auto separator_parser = fakeit::Mock<parser::rule_parser>{};
		fakeit::When(Method(separator_parser, parse))
			.Return(parser::parsing_result{{}, lexer::token_span{tokens}.subspan(2)});
		fakeit::Fake(Dtor(separator_parser));

		const auto list_parser =
			parser::rule_parser::pointer{&general_parser.get()}
			% parser::rule_parser::pointer{&separator_parser.get()};
		const auto [ast, rest_tokens] = list_parser->parse(tokens);
		REQUIRE(ast.has_value());
		CHECK(*ast == parser::ast_node{type, {}, {
			parser::ast_node{"identifier", "one", {}, 1},
			parser::ast_node{type, {}, {}, 4}
		}});
		CHECK(rest_tokens == lexer::token_span{tokens}.subspan(1));

		fakeit::Verify(Method(general_parser, parse)).Once();
		fakeit::Verify(Method(separator_parser, parse)).Once();
		fakeit::VerifyNoOtherInvocations(general_parser);
		fakeit::VerifyNoOtherInvocations(separator_parser);
	}

	SECTION("with a match and with 1 repetition") {
		const auto type = (+parser::ast_node_type::sequence)._to_string();
		auto tokens = lexer::token_group{
			{"identifier", "one", 1},
			{"comma", ",", 4},
			{"identifier", "two", 5},
			{"semicolon", ";", 8},
			{"three", "four", 9}
		};
		auto general_parser = fakeit::Mock<parser::rule_parser>{};
		fakeit::When(Method(general_parser, parse))
			.Return(parser::parsing_result{
				parser::ast_node{"identifier", "one", {}, 1},
				lexer::token_span{tokens}.subspan(1)
			})
			.Return(parser::parsing_result{
				parser::ast_node{"identifier", "two", {}, 5},
				lexer::token_span{tokens}.subspan(3)
			});
		fakeit::Fake(Dtor(general_parser));

		auto separator_parser = fakeit::Mock<parser::rule_parser>{};
		fakeit::When(Method(separator_parser, parse))
			.Return(parser::parsing_result{
				parser::ast_node{"comma", ",", {}, 4},
				lexer::token_span{tokens}.subspan(2)
			})
			.Return(parser::parsing_result{{}, lexer::token_span{tokens}.subspan(4)});
		fakeit::Fake(Dtor(separator_parser));

		const auto list_parser =
			parser::rule_parser::pointer{&general_parser.get()}
			% parser::rule_parser::pointer{&separator_parser.get()};
		const auto [ast, rest_tokens] = list_parser->parse(tokens);
		REQUIRE(ast.has_value());
		CHECK(*ast == parser::ast_node{type, {}, {
			parser::ast_node{"identifier", "one", {}, 1},
			parser::ast_node{type, {}, {
				parser::ast_node{type, {}, {
					parser::ast_node{"comma", ",", {}, 4},
					parser::ast_node{"identifier", "two", {}, 5}
				}},
				parser::ast_node{type, {}, {}, 8}
			}}
		}});
		CHECK(rest_tokens == lexer::token_span{tokens}.subspan(3));

		fakeit::Verify(Method(general_parser, parse)).Exactly(2_Times);
		fakeit::Verify(Method(separator_parser, parse)).Exactly(2_Times);
		fakeit::VerifyNoOtherInvocations(general_parser);
		fakeit::VerifyNoOtherInvocations(separator_parser);
	}

	SECTION("with a match and with 2 repetitions") {
		const auto type = (+parser::ast_node_type::sequence)._to_string();
		auto tokens = lexer::token_group{
			{"identifier", "one", 1},
			{"comma", ",", 4},
			{"identifier", "two", 5},
			{"comma", ",", 8},
			{"identifier", "three", 9},
			{"semicolon", ";", 14},
			{"four", "five", 15}
		};
		auto general_parser = fakeit::Mock<parser::rule_parser>{};
		fakeit::When(Method(general_parser, parse))
			.Return(parser::parsing_result{
				parser::ast_node{"identifier", "one", {}, 1},
				lexer::token_span{tokens}.subspan(1)
			})
			.Return(parser::parsing_result{
				parser::ast_node{"identifier", "two", {}, 5},
				lexer::token_span{tokens}.subspan(3)
			})
			.Return(parser::parsing_result{
				parser::ast_node{"identifier", "three", {}, 9},
				lexer::token_span{tokens}.subspan(5)
			});
		fakeit::Fake(Dtor(general_parser));

		auto separator_parser = fakeit::Mock<parser::rule_parser>{};
		fakeit::When(Method(separator_parser, parse))
			.Return(parser::parsing_result{
				parser::ast_node{"comma", ",", {}, 4},
				lexer::token_span{tokens}.subspan(2)
			})
			.Return(parser::parsing_result{
				parser::ast_node{"comma", ",", {}, 8},
				lexer::token_span{tokens}.subspan(4)
			})
			.Return(parser::parsing_result{{}, lexer::token_span{tokens}.subspan(6)});
		fakeit::Fake(Dtor(separator_parser));

		const auto list_parser =
			parser::rule_parser::pointer{&general_parser.get()}
			% parser::rule_parser::pointer{&separator_parser.get()};
		const auto [ast, rest_tokens] = list_parser->parse(tokens);
		REQUIRE(ast.has_value());
		CHECK(*ast == parser::ast_node{type, {}, {
			parser::ast_node{"identifier", "one", {}, 1},
			parser::ast_node{type, {}, {
				parser::ast_node{type, {}, {
					parser::ast_node{"comma", ",", {}, 4},
					parser::ast_node{"identifier", "two", {}, 5}
				}},
				parser::ast_node{type, {}, {
					parser::ast_node{type, {}, {
						parser::ast_node{"comma", ",", {}, 8},
						parser::ast_node{"identifier", "three", {}, 9}
					}},
					parser::ast_node{type, {}, {}, 14}
				}}
			}}
		}});
		CHECK(rest_tokens == lexer::token_span{tokens}.subspan(5));

		fakeit::Verify(Method(general_parser, parse)).Exactly(3_Times);
		fakeit::Verify(Method(separator_parser, parse)).Exactly(3_Times);
		fakeit::VerifyNoOtherInvocations(general_parser);
		fakeit::VerifyNoOtherInvocations(separator_parser);
	}
}
