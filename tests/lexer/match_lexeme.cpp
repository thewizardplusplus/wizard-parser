#include "../../source/thewizardplusplus/wizard_parser/lexer/lexeme.hpp"
#include "../vendor/catch/catch.hpp"
#include <regex>

TEST_CASE("lexer::match_lexeme() function", "[lexer]") {
	using namespace thewizardplusplus::wizard_parser;

	SECTION("success") {
		const auto match = lexer::match_lexeme(
			{std::regex{"[[:alpha:]]+"}},
			"test 23"
		);
		CHECK(match.str() == "test");
	}

	SECTION("failure without a match") {
		const auto match = lexer::match_lexeme(
			{std::regex{"[[:punct:]]+"}},
			"test 23"
		);
		CHECK(match.empty());
	}

	SECTION("failure with a match not at the beginning") {
		const auto match = lexer::match_lexeme(
			{std::regex{"[[:digit:]]+"}},
			"test 23"
		);
		CHECK(match.empty());
	}
}
