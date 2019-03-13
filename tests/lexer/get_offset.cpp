#include "../../source/thewizardplusplus/wizard_parser/lexer/token.hpp"
#include "../../source/thewizardplusplus/wizard_parser/utilities/utilities.hpp"
#include "../vendor/catch/catch.hpp"

TEST_CASE("lexer::get_offset() function", "[lexer]") {
	using namespace thewizardplusplus::wizard_parser;

	SECTION("without tokens") {
		const auto offset = lexer::get_offset({});
		CHECK(offset == utilities::integral_infinity);
	}

	SECTION("with tokens") {
		auto tokens = lexer::token_group{{"one", "two", 1}, {"three", "four", 4}};
		const auto offset = lexer::get_offset(tokens);
		CHECK(offset == 1);
	}
}
