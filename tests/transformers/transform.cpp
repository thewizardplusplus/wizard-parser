#include "../../source/thewizardplusplus/wizard_parser/transformers/transform.hpp"
#include "../../source/thewizardplusplus/wizard_parser/parser/ast_node.hpp"
#include "../vendor/catch/catch.hpp"

TEST_CASE("transformers::transform() function", "[transformers]") {
	using namespace thewizardplusplus::wizard_parser;

	SECTION("without children") {
		auto counter = 0;
		const auto ast = transformers::transform(
			{"one", "two", {}, 1},
			[&] (const auto& ast) {
				const auto index = parser::ast_node{"index", std::to_string(counter++), {}};
				return parser::ast_node{"bucket", {}, {ast, index}};
			}
		);
		CHECK(ast == parser::ast_node{"bucket", {}, {
			{"one", "two", {}, 1},
			{"index", "0", {}}
		}});
	}

	SECTION("with few nested children") {
		auto counter = 0;
		const auto ast = transformers::transform(
			{"one", {}, {
				{"two", "three", {}, 1},
				{"four", {}, {{"five", "six", {}, 6}, {"seven", "eight", {}, 9}}}
			}},
			[&] (const auto& ast) {
				const auto index = parser::ast_node{"index", std::to_string(counter++), {}};
				return parser::ast_node{"bucket", {}, {ast, index}};
			}
		);
		CHECK(ast == parser::ast_node{"bucket", {}, {
			{"one", {}, {
				{"bucket", {}, {{"two", "three", {}, 1}, {"index", "0", {}}}},
				{"bucket", {}, {
					{"four", {}, {
						{"bucket", {}, {{"five", "six", {}, 6}, {"index", "1", {}}}},
						{"bucket", {}, {{"seven", "eight", {}, 9}, {"index", "2", {}}}}
					}},
					{"index", "3", {}}
				}}
			}},
			{"index", "4", {}}
		}});
	}
}
