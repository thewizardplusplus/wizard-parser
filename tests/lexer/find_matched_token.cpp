#include "../../source/thewizardplusplus/wizard_parser/lexer/token.hpp"
#include "../vendor/catch/catch.hpp"
#include <regex>

TEST_CASE("lexer::find_matched_token() function", "[lexer]") {
	using namespace thewizardplusplus::wizard_parser;

	SECTION("success with one matching lexeme") {
		const auto token = lexer::find_matched_token(
			{
				{std::regex{"[[:alpha:]]+"}, "alpha"},
				{std::regex{"[[:digit:]]+"}, "digit"}
			},
			"23 tests"
		);
		REQUIRE(token.has_value());
		CHECK(*token == lexer::token{"digit", "23"});
	}

	SECTION("success with few matching lexemes") {
		const auto token = lexer::find_matched_token(
			{
				{std::regex{"[[:alnum:]]+"}, "alnum"},
				{std::regex{"[[:digit:]]+"}, "digit"}
			},
			"23 tests"
		);
		REQUIRE(token.has_value());
		CHECK(*token == lexer::token{"alnum", "23"});
	}

	SECTION("failure without matching lexemes") {
		const auto token = lexer::find_matched_token(
			{
				{std::regex{"[[:alpha:]]+"}, "alpha"},
				{std::regex{"[[:punct:]]+"}, "punct"}
			},
			"23 tests"
		);
		CHECK(!token.has_value());
	}

	SECTION("failure without lexemes") {
		const auto token = lexer::find_matched_token({}, "23 tests");
		CHECK(!token.has_value());
	}

	SECTION("failure without a code") {
		const auto token = lexer::find_matched_token(
			{
				{std::regex{"[[:alpha:]]+"}, "alpha"},
				{std::regex{"[[:digit:]]+"}, "digit"}
			},
			{}
		);
		CHECK(!token.has_value());
	}
}
