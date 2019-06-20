#include "../../source/thewizardplusplus/wizard_parser/exceptions/unexpected_entity_exception.hpp"
#include "../../source/thewizardplusplus/wizard_parser/parser/rule_parser.hpp"
#include "../../source/thewizardplusplus/wizard_parser/parser/ast_node.hpp"
#include "../../source/thewizardplusplus/wizard_parser/parser/parse.hpp"
#include "../../source/thewizardplusplus/wizard_parser/lexer/token.hpp"
#include "../vendor/catch/catch.hpp"
#include "../vendor/fakeit/fakeit.hpp"
#include <optional>

TEST_CASE("parser::parse_all() function", "[parser]") {
	using namespace thewizardplusplus::wizard_parser;

	SECTION("without tokens") {
		const auto type = exceptions::entity_type::eoi;
		auto mock_parser = fakeit::Mock<parser::rule_parser>{};
		fakeit::When(Method(mock_parser, parse))
			.Return(parser::parsing_result{});
		fakeit::Fake(Dtor(mock_parser));

		auto ast = std::optional<parser::ast_node>{};
		const auto mock_parser_pointer =
			parser::rule_parser::pointer{&mock_parser.get()};
		const auto call = [&] {
			ast = parser::parse_all(mock_parser_pointer, {}, {});
		};
		CHECK_THROWS_AS(call(), exceptions::unexpected_entity_exception<type>);
		CHECK(!ast.has_value());

		fakeit::Verify(Method(mock_parser, parse)).Once();
		fakeit::VerifyNoOtherInvocations(mock_parser);
	}

	SECTION("without a match and without rest") {
		const auto type = exceptions::entity_type::eoi;
		auto mock_parser = fakeit::Mock<parser::rule_parser>{};
		fakeit::When(Method(mock_parser, parse))
			.Return(parser::parsing_result{});
		fakeit::Fake(Dtor(mock_parser));

		auto ast = std::optional<parser::ast_node>{};
		const auto mock_parser_pointer =
			parser::rule_parser::pointer{&mock_parser.get()};
		const auto call = [&] {
			auto tokens = lexer::token_group{
				{"identifier", "one", 1},
				{"comma", ",", 4},
				{"identifier", "two", 5},
				{"comma", ",", 8},
				{"identifier", "three", 9},
				{"semicolon", ";", 14}
			};
			ast = parser::parse_all(mock_parser_pointer, tokens, {});
		};
		CHECK_THROWS_AS(call(), exceptions::unexpected_entity_exception<type>);
		CHECK(!ast.has_value());

		fakeit::Verify(Method(mock_parser, parse)).Once();
		fakeit::VerifyNoOtherInvocations(mock_parser);
	}

	SECTION("without a match and with rest") {
		const auto sequence_type = (+parser::ast_node_type::sequence)._to_string();
		const auto nothing_type = (+parser::ast_node_type::nothing)._to_string();
		const auto exception_type = exceptions::entity_type::token;
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

		auto ast = std::optional<parser::ast_node>{};
		const auto mock_parser_pointer =
			parser::rule_parser::pointer{&mock_parser.get()};
		const auto call = [&] {
			ast = parser::parse_all(mock_parser_pointer, tokens, {});
		};
		CHECK_THROWS_AS(
			call(),
			exceptions::unexpected_entity_exception<exception_type>
		);
		CHECK(!ast.has_value());

		fakeit::Verify(Method(mock_parser, parse)).Once();
		fakeit::VerifyNoOtherInvocations(mock_parser);
	}

	SECTION("with a match and without rest") {
		const auto sequence_type = (+parser::ast_node_type::sequence)._to_string();
		const auto nothing_type = (+parser::ast_node_type::nothing)._to_string();
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
				{}
			});
		fakeit::Fake(Dtor(mock_parser));

		auto ast = std::optional<parser::ast_node>{};
		const auto mock_parser_pointer =
			parser::rule_parser::pointer{&mock_parser.get()};
		const auto call = [&] {
			auto tokens = lexer::token_group{
				{"identifier", "one", 1},
				{"comma", ",", 4},
				{"identifier", "two", 5},
				{"comma", ",", 8},
				{"identifier", "three", 9}
			};
			ast = parser::parse_all(mock_parser_pointer, tokens, {});
		};
		CHECK_NOTHROW(call());
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

		fakeit::Verify(Method(mock_parser, parse)).Once();
		fakeit::VerifyNoOtherInvocations(mock_parser);
	}

	SECTION("with a match and with rest") {
		const auto sequence_type = (+parser::ast_node_type::sequence)._to_string();
		const auto nothing_type = (+parser::ast_node_type::nothing)._to_string();
		const auto exception_type = exceptions::entity_type::token;
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

		auto ast = std::optional<parser::ast_node>{};
		const auto mock_parser_pointer =
			parser::rule_parser::pointer{&mock_parser.get()};
		const auto call = [&] {
			ast = parser::parse_all(mock_parser_pointer, tokens, {});
		};
		CHECK_THROWS_AS(
			call(),
			exceptions::unexpected_entity_exception<exception_type>
		);
		CHECK(!ast.has_value());

		fakeit::Verify(Method(mock_parser, parse)).Once();
		fakeit::VerifyNoOtherInvocations(mock_parser);
	}
}
