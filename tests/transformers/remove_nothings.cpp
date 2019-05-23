#include "../../source/thewizardplusplus/wizard_parser/transformers/transformers.hpp"
#include "../../source/thewizardplusplus/wizard_parser/parser/ast_node.hpp"
#include "../vendor/catch/catch.hpp"

TEST_CASE("transformers::remove_nothings() function", "[transformers]") {
	using namespace thewizardplusplus::wizard_parser;

	SECTION("without children") {
		const auto ast = transformers::remove_nothings({"one", "two", {}, 1});
		CHECK(ast == parser::ast_node{"one", "two", {}, 1});
	}

	SECTION("without nothing children") {
		const auto ast = transformers::remove_nothings({"one", {}, {
			{"two", "three", {}, 1},
			{"four", "five", {}, 6}
		}});
		CHECK(ast == parser::ast_node{"one", {}, {
			{"two", "three", {}, 1},
			{"four", "five", {}, 6}
		}});
	}

	SECTION("with few nothing children") {
		const auto type = (+parser::ast_node_type::nothing)._to_string();
		const auto ast = transformers::remove_nothings({"one", {}, {
			{"two", "three", {}, 1},
			{type, {}, {}, 6},
			{"four", "five", {}, 7},
			{type, {}, {}, 11}
		}});
		CHECK(ast == parser::ast_node{"one", {}, {
			{"two", "three", {}, 1},
			{"four", "five", {}, 7}
		}});
	}
}
