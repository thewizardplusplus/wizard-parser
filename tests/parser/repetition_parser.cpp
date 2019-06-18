#include "../../source/thewizardplusplus/wizard_parser/parser/rule_parser.hpp"
#include "../../source/thewizardplusplus/wizard_parser/parser/repetition_parser.hpp"
#include "../../source/thewizardplusplus/wizard_parser/lexer/token.hpp"
#include "../../source/thewizardplusplus/wizard_parser/parser/ast_node.hpp"
#include "../vendor/catch/catch.hpp"
#include "../vendor/fakeit/fakeit.hpp"

TEST_CASE("parser::repetition_parser class", "[parser][repetition_parser]") {
	using namespace thewizardplusplus::wizard_parser;
	using namespace thewizardplusplus::wizard_parser::parser::operators;
	using namespace fakeit;

	SECTION("repetition from 2 to 5 times without tokens") {
		auto mock_parser = fakeit::Mock<parser::rule_parser>{};
		fakeit::When(Method(mock_parser, parse))
			.Return(parser::parsing_result{});
		fakeit::Fake(Dtor(mock_parser));

		const auto repetition_parser =
			std::make_shared<parser::repetition_parser>(
				parser::rule_parser::pointer{&mock_parser.get()},
				2,
				5
			);
		const auto [ast, rest_tokens] = repetition_parser->parse({});
		CHECK(!ast.has_value());
		CHECK(rest_tokens.empty());

		fakeit::Verify(Method(mock_parser, parse)).Once();
		fakeit::VerifyNoOtherInvocations(mock_parser);
	}

	SECTION("repetition from 2 to 5 times without matches") {
		auto tokens = lexer::token_group{
			{"one", "two", 1},
			{"one", "two", 4},
			{"one", "two", 7},
			{"one", "two", 10},
			{"one", "two", 13},
			{"one", "two", 16},
			{"three", "four", 19},
			{"five", "six", 23}
		};
		auto mock_parser = fakeit::Mock<parser::rule_parser>{};
		fakeit::When(Method(mock_parser, parse))
			.Return(parser::parsing_result{{}, lexer::token_span{tokens}.subspan(1)});
		fakeit::Fake(Dtor(mock_parser));

		const auto repetition_parser =
			std::make_shared<parser::repetition_parser>(
				parser::rule_parser::pointer{&mock_parser.get()},
				2,
				5
			);
		const auto [ast, rest_tokens] = repetition_parser->parse(tokens);
		CHECK(!ast.has_value());
		CHECK(rest_tokens == lexer::token_span{tokens});

		fakeit::Verify(Method(mock_parser, parse)).Once();
		fakeit::VerifyNoOtherInvocations(mock_parser);
	}

	SECTION("repetition from 2 to 5 times with 1 match") {
		auto tokens = lexer::token_group{
			{"one", "two", 16},
			{"three", "four", 19},
			{"five", "six", 23}
		};
		auto mock_parser = fakeit::Mock<parser::rule_parser>{};
		fakeit::When(Method(mock_parser, parse))
			.Return(parser::parsing_result{
				parser::ast_node{"one", "two", {}, 16},
				lexer::token_span{tokens}.subspan(1)
			})
			.Return(parser::parsing_result{{}, lexer::token_span{tokens}.subspan(1)});
		fakeit::Fake(Dtor(mock_parser));

		const auto repetition_parser =
			std::make_shared<parser::repetition_parser>(
				parser::rule_parser::pointer{&mock_parser.get()},
				2,
				5
			);
		const auto [ast, rest_tokens] = repetition_parser->parse(tokens);
		CHECK(!ast.has_value());
		CHECK(rest_tokens == lexer::token_span{tokens}.subspan(1));

		fakeit::Verify(Method(mock_parser, parse)).Exactly(2_Times);
		fakeit::VerifyNoOtherInvocations(mock_parser);
	}

	SECTION("repetition from 2 to 5 times with 2 matches") {
		const auto type = (+parser::ast_node_type::sequence)._to_string();
		auto tokens = lexer::token_group{
			{"one", "two", 13},
			{"one", "two", 16},
			{"three", "four", 19},
			{"five", "six", 23}
		};
		auto mock_parser = fakeit::Mock<parser::rule_parser>{};
		fakeit::When(Method(mock_parser, parse))
			.Return(parser::parsing_result{
				parser::ast_node{"one", "two", {}, 13},
				lexer::token_span{tokens}.subspan(1)
			})
			.Return(parser::parsing_result{
				parser::ast_node{"one", "two", {}, 16},
				lexer::token_span{tokens}.subspan(2)
			})
			.Return(parser::parsing_result{{}, lexer::token_span{tokens}.subspan(2)});
		fakeit::Fake(Dtor(mock_parser));

		const auto repetition_parser =
			std::make_shared<parser::repetition_parser>(
				parser::rule_parser::pointer{&mock_parser.get()},
				2,
				5
			);
		const auto [ast, rest_tokens] = repetition_parser->parse(tokens);
		REQUIRE(ast.has_value());
		CHECK(*ast == parser::ast_node{type, {}, {
			parser::ast_node{"one", "two", {}, 13},
			parser::ast_node{type, {}, {
				parser::ast_node{"one", "two", {}, 16},
				parser::ast_node{type, {}, {}, 19}
			}}
		}});
		CHECK(rest_tokens == lexer::token_span{tokens}.subspan(2));

		fakeit::Verify(Method(mock_parser, parse)).Exactly(3_Times);
		fakeit::VerifyNoOtherInvocations(mock_parser);
	}

	SECTION("repetition from 2 to 5 times with 3 matches") {
		const auto type = (+parser::ast_node_type::sequence)._to_string();
		auto tokens = lexer::token_group{
			{"one", "two", 10},
			{"one", "two", 13},
			{"one", "two", 16},
			{"three", "four", 19},
			{"five", "six", 23}
		};
		auto mock_parser = fakeit::Mock<parser::rule_parser>{};
		fakeit::When(Method(mock_parser, parse))
			.Return(parser::parsing_result{
				parser::ast_node{"one", "two", {}, 10},
				lexer::token_span{tokens}.subspan(1)
			})
			.Return(parser::parsing_result{
				parser::ast_node{"one", "two", {}, 13},
				lexer::token_span{tokens}.subspan(2)
			})
			.Return(parser::parsing_result{
				parser::ast_node{"one", "two", {}, 16},
				lexer::token_span{tokens}.subspan(3)
			})
			.Return(parser::parsing_result{{}, lexer::token_span{tokens}.subspan(3)});
		fakeit::Fake(Dtor(mock_parser));

		const auto repetition_parser =
			std::make_shared<parser::repetition_parser>(
				parser::rule_parser::pointer{&mock_parser.get()},
				2,
				5
			);
		const auto [ast, rest_tokens] = repetition_parser->parse(tokens);
		REQUIRE(ast.has_value());
		CHECK(*ast == parser::ast_node{type, {}, {
			parser::ast_node{"one", "two", {}, 10},
			parser::ast_node{type, {}, {
				parser::ast_node{"one", "two", {}, 13},
				parser::ast_node{type, {}, {
					parser::ast_node{"one", "two", {}, 16},
					parser::ast_node{type, {}, {}, 19}
				}}
			}}
		}});
		CHECK(rest_tokens == lexer::token_span{tokens}.subspan(3));

		fakeit::Verify(Method(mock_parser, parse)).Exactly(4_Times);
		fakeit::VerifyNoOtherInvocations(mock_parser);
	}

	SECTION("repetition from 2 to 5 times with 4 matches") {
		const auto type = (+parser::ast_node_type::sequence)._to_string();
		auto tokens = lexer::token_group{
			{"one", "two", 7},
			{"one", "two", 10},
			{"one", "two", 13},
			{"one", "two", 16},
			{"three", "four", 19},
			{"five", "six", 23}
		};
		auto mock_parser = fakeit::Mock<parser::rule_parser>{};
		fakeit::When(Method(mock_parser, parse))
			.Return(parser::parsing_result{
				parser::ast_node{"one", "two", {}, 7},
				lexer::token_span{tokens}.subspan(1)
			})
			.Return(parser::parsing_result{
				parser::ast_node{"one", "two", {}, 10},
				lexer::token_span{tokens}.subspan(2)
			})
			.Return(parser::parsing_result{
				parser::ast_node{"one", "two", {}, 13},
				lexer::token_span{tokens}.subspan(3)
			})
			.Return(parser::parsing_result{
				parser::ast_node{"one", "two", {}, 16},
				lexer::token_span{tokens}.subspan(4)
			})
			.Return(parser::parsing_result{{}, lexer::token_span{tokens}.subspan(4)});
		fakeit::Fake(Dtor(mock_parser));

		const auto repetition_parser =
			std::make_shared<parser::repetition_parser>(
				parser::rule_parser::pointer{&mock_parser.get()},
				2,
				5
			);
		const auto [ast, rest_tokens] = repetition_parser->parse(tokens);
		REQUIRE(ast.has_value());
		CHECK(*ast == parser::ast_node{type, {}, {
			parser::ast_node{"one", "two", {}, 7},
			parser::ast_node{type, {}, {
				parser::ast_node{"one", "two", {}, 10},
				parser::ast_node{type, {}, {
					parser::ast_node{"one", "two", {}, 13},
					parser::ast_node{type, {}, {
						parser::ast_node{"one", "two", {}, 16},
						parser::ast_node{type, {}, {}, 19}
					}}
				}}
			}}
		}});
		CHECK(rest_tokens == lexer::token_span{tokens}.subspan(4));

		fakeit::Verify(Method(mock_parser, parse)).Exactly(5_Times);
		fakeit::VerifyNoOtherInvocations(mock_parser);
	}

	SECTION("repetition from 2 to 5 times with 5 matches") {
		const auto type = (+parser::ast_node_type::sequence)._to_string();
		auto tokens = lexer::token_group{
			{"one", "two", 4},
			{"one", "two", 7},
			{"one", "two", 10},
			{"one", "two", 13},
			{"one", "two", 16},
			{"three", "four", 19},
			{"five", "six", 23}
		};
		auto mock_parser = fakeit::Mock<parser::rule_parser>{};
		fakeit::When(Method(mock_parser, parse))
			.Return(parser::parsing_result{
				parser::ast_node{"one", "two", {}, 4},
				lexer::token_span{tokens}.subspan(1)
			})
			.Return(parser::parsing_result{
				parser::ast_node{"one", "two", {}, 7},
				lexer::token_span{tokens}.subspan(2)
			})
			.Return(parser::parsing_result{
				parser::ast_node{"one", "two", {}, 10},
				lexer::token_span{tokens}.subspan(3)
			})
			.Return(parser::parsing_result{
				parser::ast_node{"one", "two", {}, 13},
				lexer::token_span{tokens}.subspan(4)
			})
			.Return(parser::parsing_result{
				parser::ast_node{"one", "two", {}, 16},
				lexer::token_span{tokens}.subspan(5)
			})
			.Return(parser::parsing_result{{}, lexer::token_span{tokens}.subspan(5)});
		fakeit::Fake(Dtor(mock_parser));

		const auto repetition_parser =
			std::make_shared<parser::repetition_parser>(
				parser::rule_parser::pointer{&mock_parser.get()},
				2,
				5
			);
		const auto [ast, rest_tokens] = repetition_parser->parse(tokens);
		REQUIRE(ast.has_value());
		CHECK(*ast == parser::ast_node{type, {}, {
			parser::ast_node{"one", "two", {}, 4},
			parser::ast_node{type, {}, {
				parser::ast_node{"one", "two", {}, 7},
				parser::ast_node{type, {}, {
					parser::ast_node{"one", "two", {}, 10},
					parser::ast_node{type, {}, {
						parser::ast_node{"one", "two", {}, 13},
						parser::ast_node{type, {}, {
							parser::ast_node{"one", "two", {}, 16},
							parser::ast_node{type, {}, {}, 19}
						}}
					}}
				}}
			}}
		}});
		CHECK(rest_tokens == lexer::token_span{tokens}.subspan(5));

		fakeit::Verify(Method(mock_parser, parse)).Exactly(5_Times);
		fakeit::VerifyNoOtherInvocations(mock_parser);
	}

	SECTION("repetition from 2 to 5 times with 6 matches") {
		const auto type = (+parser::ast_node_type::sequence)._to_string();
		auto tokens = lexer::token_group{
			{"one", "two", 1},
			{"one", "two", 4},
			{"one", "two", 7},
			{"one", "two", 10},
			{"one", "two", 13},
			{"one", "two", 16},
			{"three", "four", 19},
			{"five", "six", 23}
		};
		auto mock_parser = fakeit::Mock<parser::rule_parser>{};
		fakeit::When(Method(mock_parser, parse))
			.Return(parser::parsing_result{
				parser::ast_node{"one", "two", {}, 1},
				lexer::token_span{tokens}.subspan(1)
			})
			.Return(parser::parsing_result{
				parser::ast_node{"one", "two", {}, 4},
				lexer::token_span{tokens}.subspan(2)
			})
			.Return(parser::parsing_result{
				parser::ast_node{"one", "two", {}, 7},
				lexer::token_span{tokens}.subspan(3)
			})
			.Return(parser::parsing_result{
				parser::ast_node{"one", "two", {}, 10},
				lexer::token_span{tokens}.subspan(4)
			})
			.Return(parser::parsing_result{
				parser::ast_node{"one", "two", {}, 13},
				lexer::token_span{tokens}.subspan(5)
			})
			.Return(parser::parsing_result{
				parser::ast_node{"one", "two", {}, 16},
				lexer::token_span{tokens}.subspan(6)
			});
		fakeit::Fake(Dtor(mock_parser));

		const auto repetition_parser =
			std::make_shared<parser::repetition_parser>(
				parser::rule_parser::pointer{&mock_parser.get()},
				2,
				5
			);
		const auto [ast, rest_tokens] = repetition_parser->parse(tokens);
		REQUIRE(ast.has_value());
		CHECK(*ast == parser::ast_node{type, {}, {
			parser::ast_node{"one", "two", {}, 1},
			parser::ast_node{type, {}, {
				parser::ast_node{"one", "two", {}, 4},
				parser::ast_node{type, {}, {
					parser::ast_node{"one", "two", {}, 7},
					parser::ast_node{type, {}, {
						parser::ast_node{"one", "two", {}, 10},
						parser::ast_node{type, {}, {
							parser::ast_node{"one", "two", {}, 13},
							parser::ast_node{type, {}, {}, 16}
						}}
					}}
				}}
			}}
		}});
		CHECK(rest_tokens == lexer::token_span{tokens}.subspan(5));

		fakeit::Verify(Method(mock_parser, parse)).Exactly(5_Times);
		fakeit::VerifyNoOtherInvocations(mock_parser);
	}

	SECTION("optionality without tokens") {
		const auto type = (+parser::ast_node_type::sequence)._to_string();
		auto mock_parser = fakeit::Mock<parser::rule_parser>{};
		fakeit::When(Method(mock_parser, parse))
			.Return(parser::parsing_result{});
		fakeit::Fake(Dtor(mock_parser));

		const auto repetition_parser =
			-parser::rule_parser::pointer{&mock_parser.get()};
		const auto [ast, rest_tokens] = repetition_parser->parse({});
		REQUIRE(ast.has_value());
		CHECK(*ast == parser::ast_node{type, {}, {}, lexer::get_offset({})});
		CHECK(rest_tokens.empty());

		fakeit::Verify(Method(mock_parser, parse)).Once();
		fakeit::VerifyNoOtherInvocations(mock_parser);
	}

	SECTION("optionality without a match") {
		const auto type = (+parser::ast_node_type::sequence)._to_string();
		auto tokens = lexer::token_group{{"three", "four", 19}, {"five", "six", 23}};
		auto mock_parser = fakeit::Mock<parser::rule_parser>{};
		fakeit::When(Method(mock_parser, parse))
			.Return(parser::parsing_result{{}, lexer::token_span{tokens}.subspan(1)});
		fakeit::Fake(Dtor(mock_parser));

		const auto repetition_parser =
			-parser::rule_parser::pointer{&mock_parser.get()};
		const auto [ast, rest_tokens] = repetition_parser->parse(tokens);
		REQUIRE(ast.has_value());
		CHECK(*ast == parser::ast_node{type, {}, {}, 19});
		CHECK(rest_tokens == lexer::token_span{tokens});

		fakeit::Verify(Method(mock_parser, parse)).Once();
		fakeit::VerifyNoOtherInvocations(mock_parser);
	}

	SECTION("optionality with a match") {
		const auto type = (+parser::ast_node_type::sequence)._to_string();
		auto tokens = lexer::token_group{
			{"one", "two", 1},
			{"one", "two", 4},
			{"one", "two", 7},
			{"one", "two", 10},
			{"one", "two", 13},
			{"one", "two", 16},
			{"three", "four", 19},
			{"five", "six", 23}
		};
		auto mock_parser = fakeit::Mock<parser::rule_parser>{};
		fakeit::When(Method(mock_parser, parse))
			.Return(parser::parsing_result{
				parser::ast_node{"one", "two", {}, 1},
				lexer::token_span{tokens}.subspan(1)
			})
			.Return(parser::parsing_result{{}, lexer::token_span{tokens}.subspan(1)});
		fakeit::Fake(Dtor(mock_parser));

		const auto repetition_parser =
			-parser::rule_parser::pointer{&mock_parser.get()};
		const auto [ast, rest_tokens] = repetition_parser->parse(tokens);
		REQUIRE(ast.has_value());
		CHECK(*ast == parser::ast_node{type, {}, {
			parser::ast_node{"one", "two", {}, 1},
			parser::ast_node{type, {}, {}, 4}
		}});
		CHECK(rest_tokens == lexer::token_span{tokens}.subspan(1));

		fakeit::Verify(Method(mock_parser, parse)).Once();
		fakeit::VerifyNoOtherInvocations(mock_parser);
	}

	SECTION("repetition from 0 to infinity times without tokens") {
		const auto type = (+parser::ast_node_type::sequence)._to_string();
		auto mock_parser = fakeit::Mock<parser::rule_parser>{};
		fakeit::When(Method(mock_parser, parse))
			.Return(parser::parsing_result{});
		fakeit::Fake(Dtor(mock_parser));

		const auto repetition_parser =
			*parser::rule_parser::pointer{&mock_parser.get()};
		const auto [ast, rest_tokens] = repetition_parser->parse({});
		REQUIRE(ast.has_value());
		CHECK(*ast == parser::ast_node{type, {}, {}, lexer::get_offset({})});
		CHECK(rest_tokens.empty());

		fakeit::Verify(Method(mock_parser, parse)).Once();
		fakeit::VerifyNoOtherInvocations(mock_parser);
	}

	SECTION("repetition from 0 to infinity times without matches") {
		const auto type = (+parser::ast_node_type::sequence)._to_string();
		auto tokens = lexer::token_group{{"three", "four", 19}, {"five", "six", 23}};
		auto mock_parser = fakeit::Mock<parser::rule_parser>{};
		fakeit::When(Method(mock_parser, parse))
			.Return(parser::parsing_result{{}, lexer::token_span{tokens}.subspan(1)});
		fakeit::Fake(Dtor(mock_parser));

		const auto repetition_parser =
			*parser::rule_parser::pointer{&mock_parser.get()};
		const auto [ast, rest_tokens] = repetition_parser->parse(tokens);
		REQUIRE(ast.has_value());
		CHECK(*ast == parser::ast_node{type, {}, {}, 19});
		CHECK(rest_tokens == lexer::token_span{tokens});

		fakeit::Verify(Method(mock_parser, parse)).Once();
		fakeit::VerifyNoOtherInvocations(mock_parser);
	}

	SECTION("repetition from 0 to infinity times with matches") {
		const auto type = (+parser::ast_node_type::sequence)._to_string();
		auto tokens = lexer::token_group{
			{"one", "two", 1},
			{"one", "two", 4},
			{"one", "two", 7},
			{"one", "two", 10},
			{"one", "two", 13},
			{"one", "two", 16},
			{"three", "four", 19},
			{"five", "six", 23}
		};
		auto mock_parser = fakeit::Mock<parser::rule_parser>{};
		fakeit::When(Method(mock_parser, parse))
			.Return(parser::parsing_result{
				parser::ast_node{"one", "two", {}, 1},
				lexer::token_span{tokens}.subspan(1)
			})
			.Return(parser::parsing_result{
				parser::ast_node{"one", "two", {}, 4},
				lexer::token_span{tokens}.subspan(2)
			})
			.Return(parser::parsing_result{
				parser::ast_node{"one", "two", {}, 7},
				lexer::token_span{tokens}.subspan(3)
			})
			.Return(parser::parsing_result{
				parser::ast_node{"one", "two", {}, 10},
				lexer::token_span{tokens}.subspan(4)
			})
			.Return(parser::parsing_result{
				parser::ast_node{"one", "two", {}, 13},
				lexer::token_span{tokens}.subspan(5)
			})
			.Return(parser::parsing_result{
				parser::ast_node{"one", "two", {}, 16},
				lexer::token_span{tokens}.subspan(6)
			})
			.Return(parser::parsing_result{{}, lexer::token_span{tokens}.subspan(6)});
		fakeit::Fake(Dtor(mock_parser));

		const auto repetition_parser =
			*parser::rule_parser::pointer{&mock_parser.get()};
		const auto [ast, rest_tokens] = repetition_parser->parse(tokens);
		REQUIRE(ast.has_value());
		CHECK(*ast == parser::ast_node{type, {}, {
			parser::ast_node{"one", "two", {}, 1},
			parser::ast_node{type, {}, {
				parser::ast_node{"one", "two", {}, 4},
				parser::ast_node{type, {}, {
					parser::ast_node{"one", "two", {}, 7},
					parser::ast_node{type, {}, {
						parser::ast_node{"one", "two", {}, 10},
						parser::ast_node{type, {}, {
							parser::ast_node{"one", "two", {}, 13},
							parser::ast_node{type, {}, {
								parser::ast_node{"one", "two", {}, 16},
								parser::ast_node{type, {}, {}, 19}
							}}
						}}
					}}
				}}
			}}
		}});
		CHECK(rest_tokens == lexer::token_span{tokens}.subspan(6));

		fakeit::Verify(Method(mock_parser, parse)).Exactly(7_Times);
		fakeit::VerifyNoOtherInvocations(mock_parser);
	}

	SECTION("repetition from 1 to infinity times without tokens") {
		auto mock_parser = fakeit::Mock<parser::rule_parser>{};
		fakeit::When(Method(mock_parser, parse))
			.Return(parser::parsing_result{});
		fakeit::Fake(Dtor(mock_parser));

		const auto repetition_parser =
			+parser::rule_parser::pointer{&mock_parser.get()};
		const auto [ast, rest_tokens] = repetition_parser->parse({});
		CHECK(!ast.has_value());
		CHECK(rest_tokens.empty());

		fakeit::Verify(Method(mock_parser, parse)).Once();
		fakeit::VerifyNoOtherInvocations(mock_parser);
	}

	SECTION("repetition from 1 to infinity times without matches") {
		auto tokens = lexer::token_group{{"three", "four", 19}, {"five", "six", 23}};
		auto mock_parser = fakeit::Mock<parser::rule_parser>{};
		fakeit::When(Method(mock_parser, parse))
			.Return(parser::parsing_result{{}, lexer::token_span{tokens}.subspan(1)});
		fakeit::Fake(Dtor(mock_parser));

		const auto repetition_parser =
			+parser::rule_parser::pointer{&mock_parser.get()};
		const auto [ast, rest_tokens] = repetition_parser->parse(tokens);
		CHECK(!ast.has_value());
		CHECK(rest_tokens == lexer::token_span{tokens});

		fakeit::Verify(Method(mock_parser, parse)).Once();
		fakeit::VerifyNoOtherInvocations(mock_parser);
	}

	SECTION("repetition from 1 to infinity times with matches") {
		const auto type = (+parser::ast_node_type::sequence)._to_string();
		auto tokens = lexer::token_group{
			{"one", "two", 1},
			{"one", "two", 4},
			{"one", "two", 7},
			{"one", "two", 10},
			{"one", "two", 13},
			{"one", "two", 16},
			{"three", "four", 19},
			{"five", "six", 23}
		};
		auto mock_parser = fakeit::Mock<parser::rule_parser>{};
		fakeit::When(Method(mock_parser, parse))
			.Return(parser::parsing_result{
				parser::ast_node{"one", "two", {}, 1},
				lexer::token_span{tokens}.subspan(1)
			})
			.Return(parser::parsing_result{
				parser::ast_node{"one", "two", {}, 4},
				lexer::token_span{tokens}.subspan(2)
			})
			.Return(parser::parsing_result{
				parser::ast_node{"one", "two", {}, 7},
				lexer::token_span{tokens}.subspan(3)
			})
			.Return(parser::parsing_result{
				parser::ast_node{"one", "two", {}, 10},
				lexer::token_span{tokens}.subspan(4)
			})
			.Return(parser::parsing_result{
				parser::ast_node{"one", "two", {}, 13},
				lexer::token_span{tokens}.subspan(5)
			})
			.Return(parser::parsing_result{
				parser::ast_node{"one", "two", {}, 16},
				lexer::token_span{tokens}.subspan(6)
			})
			.Return(parser::parsing_result{{}, lexer::token_span{tokens}.subspan(6)});
		fakeit::Fake(Dtor(mock_parser));

		const auto repetition_parser =
			+parser::rule_parser::pointer{&mock_parser.get()};
		const auto [ast, rest_tokens] = repetition_parser->parse(tokens);
		REQUIRE(ast.has_value());
		CHECK(*ast == parser::ast_node{type, {}, {
			parser::ast_node{"one", "two", {}, 1},
			parser::ast_node{type, {}, {
				parser::ast_node{"one", "two", {}, 4},
				parser::ast_node{type, {}, {
					parser::ast_node{"one", "two", {}, 7},
					parser::ast_node{type, {}, {
						parser::ast_node{"one", "two", {}, 10},
						parser::ast_node{type, {}, {
							parser::ast_node{"one", "two", {}, 13},
							parser::ast_node{type, {}, {
								parser::ast_node{"one", "two", {}, 16},
								parser::ast_node{type, {}, {}, 19}
							}}
						}}
					}}
				}}
			}}
		}});
		CHECK(rest_tokens == lexer::token_span{tokens}.subspan(6));

		fakeit::Verify(Method(mock_parser, parse)).Exactly(7_Times);
		fakeit::VerifyNoOtherInvocations(mock_parser);
	}
}
