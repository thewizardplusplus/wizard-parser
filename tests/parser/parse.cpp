#include "../../source/thewizardplusplus/wizard_parser/parser/rule_parser.hpp"
#include "../../source/thewizardplusplus/wizard_parser/parser/parse.hpp"
#include "../../source/thewizardplusplus/wizard_parser/lexer/token.hpp"
#include "../../source/thewizardplusplus/wizard_parser/parser/ast_node.hpp"
#include "../../source/thewizardplusplus/wizard_parser/transformers/transformers.hpp"
#include "../vendor/catch/catch.hpp"
#include "../vendor/fakeit/fakeit.hpp"

TEST_CASE("parser::parse() function", "[parser]") {
	using namespace thewizardplusplus::wizard_parser;

	SECTION("without tokens") {
		auto mock_parser = fakeit::Mock<parser::rule_parser>{};
		fakeit::When(Method(mock_parser, parse))
			.Return(parser::parsing_result{});
		fakeit::Fake(Dtor(mock_parser));

		const auto mock_parser_pointer =
			parser::rule_parser::pointer{&mock_parser.get()};
		const auto [ast, rest_tokens] = parser::parse(mock_parser_pointer, {}, {});
		CHECK(!ast.has_value());
		CHECK(rest_tokens.empty());

		fakeit::Verify(Method(mock_parser, parse)).Once();
		fakeit::VerifyNoOtherInvocations(mock_parser);
	}

	SECTION("without a match") {
		auto tokens = lexer::token_group{
			{"identifier", "one", 1},
			{"comma", ",", 4},
			{"identifier", "two", 5},
			{"comma", ",", 8},
			{"identifier", "three", 9},
			{"semicolon", ";", 14}
		};
		auto mock_parser = fakeit::Mock<parser::rule_parser>{};
		fakeit::When(Method(mock_parser, parse))
			.Return(parser::parsing_result{{}, lexer::token_span{tokens}.subspan(1)});
		fakeit::Fake(Dtor(mock_parser));

		const auto mock_parser_pointer =
			parser::rule_parser::pointer{&mock_parser.get()};
		const auto [ast, rest_tokens] = parser::parse(
			mock_parser_pointer,
			tokens,
			{}
		);
		CHECK(!ast.has_value());
		CHECK(rest_tokens == lexer::token_span{tokens}.subspan(1));

		fakeit::Verify(Method(mock_parser, parse)).Once();
		fakeit::VerifyNoOtherInvocations(mock_parser);
	}

	SECTION("with a match and without handlers") {
		const auto sequence_type = (+parser::ast_node_type::sequence)._to_string();
		const auto nothing_type = (+parser::ast_node_type::nothing)._to_string();
		auto tokens = lexer::token_group{
			{"identifier", "one", 1},
			{"comma", ",", 4},
			{"identifier", "two", 5},
			{"comma", ",", 8},
			{"identifier", "three", 9},
			{"semicolon", ";", 14}
		};
		auto mock_parser = fakeit::Mock<parser::rule_parser>{};
		fakeit::When(Method(mock_parser, parse))
			.Return(parser::parsing_result{
				parser::ast_node{sequence_type, {}, {
					parser::ast_node{"identifier", "one", {}, 1},
					parser::ast_node{sequence_type, {}, {
						parser::ast_node{sequence_type, {}, {
							parser::ast_node{nothing_type, {}, {}, 4},
							parser::ast_node{"identifier", "two", {}, 5},
						}},
						parser::ast_node{sequence_type, {}, {
							parser::ast_node{sequence_type, {}, {
								parser::ast_node{nothing_type, {}, {}, 8},
								parser::ast_node{"identifier", "three", {}, 9},
							}},
							parser::ast_node{sequence_type, {}, {}, 14}
						}}
					}}
				}},
				lexer::token_span{tokens}.subspan(5)
			});
		fakeit::Fake(Dtor(mock_parser));

		const auto mock_parser_pointer =
			parser::rule_parser::pointer{&mock_parser.get()};
		const auto [ast, rest_tokens] = parser::parse(
			mock_parser_pointer,
			tokens,
			{}
		);
		REQUIRE(ast.has_value());
		CHECK(*ast == parser::ast_node{sequence_type, {}, {
			parser::ast_node{"identifier", "one", {}, 1},
			parser::ast_node{sequence_type, {}, {
				parser::ast_node{sequence_type, {}, {
					parser::ast_node{nothing_type, {}, {}, 4},
					parser::ast_node{"identifier", "two", {}, 5},
				}},
				parser::ast_node{sequence_type, {}, {
					parser::ast_node{sequence_type, {}, {
						parser::ast_node{nothing_type, {}, {}, 8},
						parser::ast_node{"identifier", "three", {}, 9},
					}},
					parser::ast_node{sequence_type, {}, {}, 14}
				}}
			}}
		}});
		CHECK(rest_tokens == lexer::token_span{tokens}.subspan(5));

		fakeit::Verify(Method(mock_parser, parse)).Once();
		fakeit::VerifyNoOtherInvocations(mock_parser);
	}

	SECTION("with a match and with any handlers") {
		const auto sequence_type = (+parser::ast_node_type::sequence)._to_string();
		const auto nothing_type = (+parser::ast_node_type::nothing)._to_string();
		auto tokens = lexer::token_group{
			{"identifier", "one", 1},
			{"comma", ",", 4},
			{"identifier", "two", 5},
			{"comma", ",", 8},
			{"identifier", "three", 9},
			{"semicolon", ";", 14}
		};
		auto mock_parser = fakeit::Mock<parser::rule_parser>{};
		fakeit::When(Method(mock_parser, parse))
			.Return(parser::parsing_result{
				parser::ast_node{sequence_type, {}, {
					parser::ast_node{"identifier", "one", {}, 1},
					parser::ast_node{sequence_type, {}, {
						parser::ast_node{sequence_type, {}, {
							parser::ast_node{nothing_type, {}, {}, 4},
							parser::ast_node{"identifier", "two", {}, 5},
						}},
						parser::ast_node{sequence_type, {}, {
							parser::ast_node{sequence_type, {}, {
								parser::ast_node{nothing_type, {}, {}, 8},
								parser::ast_node{"identifier", "three", {}, 9},
							}},
							parser::ast_node{sequence_type, {}, {}, 14}
						}}
					}}
				}},
				lexer::token_span{tokens}.subspan(5)
			});
		fakeit::Fake(Dtor(mock_parser));

		const auto mock_parser_pointer =
			parser::rule_parser::pointer{&mock_parser.get()};
		const auto [ast, rest_tokens] = parser::parse(
			mock_parser_pointer,
			tokens,
			{transformers::join_sequences}
		);
		REQUIRE(ast.has_value());
		CHECK(*ast == parser::ast_node{sequence_type, {}, {
			parser::ast_node{"identifier", "one", {}, 1},
			parser::ast_node{nothing_type, {}, {}, 4},
			parser::ast_node{"identifier", "two", {}, 5},
			parser::ast_node{nothing_type, {}, {}, 8},
			parser::ast_node{"identifier", "three", {}, 9}
		}});
		CHECK(rest_tokens == lexer::token_span{tokens}.subspan(5));

		fakeit::Verify(Method(mock_parser, parse)).Once();
		fakeit::VerifyNoOtherInvocations(mock_parser);
	}

	SECTION("with a match and with default handlers") {
		const auto sequence_type = (+parser::ast_node_type::sequence)._to_string();
		const auto nothing_type = (+parser::ast_node_type::nothing)._to_string();
		auto tokens = lexer::token_group{
			{"identifier", "one", 1},
			{"comma", ",", 4},
			{"identifier", "two", 5},
			{"comma", ",", 8},
			{"identifier", "three", 9},
			{"semicolon", ";", 14}
		};
		auto mock_parser = fakeit::Mock<parser::rule_parser>{};
		fakeit::When(Method(mock_parser, parse))
			.Return(parser::parsing_result{
				parser::ast_node{sequence_type, {}, {
					parser::ast_node{"identifier", "one", {}, 1},
					parser::ast_node{sequence_type, {}, {
						parser::ast_node{sequence_type, {}, {
							parser::ast_node{nothing_type, {}, {}, 4},
							parser::ast_node{"identifier", "two", {}, 5},
						}},
						parser::ast_node{sequence_type, {}, {
							parser::ast_node{sequence_type, {}, {
								parser::ast_node{nothing_type, {}, {}, 8},
								parser::ast_node{"identifier", "three", {}, 9},
							}},
							parser::ast_node{sequence_type, {}, {}, 14}
						}}
					}}
				}},
				lexer::token_span{tokens}.subspan(5)
			});
		fakeit::Fake(Dtor(mock_parser));

		const auto mock_parser_pointer =
			parser::rule_parser::pointer{&mock_parser.get()};
		const auto [ast, rest_tokens] = parser::parse(mock_parser_pointer, tokens);
		REQUIRE(ast.has_value());
		CHECK(*ast == parser::ast_node{sequence_type, {}, {
			parser::ast_node{"identifier", "one", {}, 1},
			parser::ast_node{"identifier", "two", {}, 5},
			parser::ast_node{"identifier", "three", {}, 9}
		}});
		CHECK(rest_tokens == lexer::token_span{tokens}.subspan(5));

		fakeit::Verify(Method(mock_parser, parse)).Once();
		fakeit::VerifyNoOtherInvocations(mock_parser);
	}
}
