#include "../../source/thewizardplusplus/wizard_parser/parser/ast_node.hpp"
#include "../../source/thewizardplusplus/wizard_parser/utilities/utilities.hpp"
#include "../vendor/catch/catch.hpp"

TEST_CASE("parser::get_offset() function", "[parser]") {
	using namespace thewizardplusplus::wizard_parser;

	SECTION("without an offset") {
		const auto offset = parser::get_offset({"one", "two", {}});
		CHECK(offset == utilities::integral_infinity);
	}

	SECTION("with an offset on a top level") {
		const auto offset = parser::get_offset({"one", "two", {}, 1});
		CHECK(offset == 1);
	}

	SECTION("with an offset on an inner level") {
		const auto offset = parser::get_offset({"one", {}, {
			{"two", "three", {}, 1},
			{"four", "five", {}, 6}
		}});
		CHECK(offset == 1);
	}
}
