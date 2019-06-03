#include "../../source/thewizardplusplus/wizard_parser/lexer/tokenize.hpp"
#include "../../source/thewizardplusplus/wizard_parser/lexer/token.hpp"
#include "../vendor/catch/catch.hpp"
#include <regex>

TEST_CASE("lexer::tokenize() function with exceptions", "[lexer]") {
	using namespace thewizardplusplus::wizard_parser;

	SECTION("without exceptions") {
		const auto [tokens, rest_offset] = lexer::tokenize(
			{
				{std::regex{"[[:alpha:]]+"}, "alpha"},
				{std::regex{"[[:digit:]]+"}, "digit"},
				{std::regex{"[[:space:]]+"}, "space"}
			},
			{},
			"test 23"
		);
		CHECK(tokens == lexer::token_group{
			{"alpha", "test", {}},
			{"space", " ", 4},
			{"digit", "23", 5}
		});
		CHECK(rest_offset == 7);
	}

	SECTION("with exceptions") {
		const auto [tokens, rest_offset] = lexer::tokenize(
			{
				{std::regex{"[[:alpha:]]+"}, "alpha"},
				{std::regex{"[[:digit:]]+"}, "digit"},
				{std::regex{"[[:space:]]+"}, "space"}
			},
			{"space"},
			"test 23"
		);
		CHECK(tokens == lexer::token_group{
			{"alpha", "test", {}},
			{"digit", "23", 5}
		});
		CHECK(rest_offset == 7);
	}
}
