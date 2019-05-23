#include "../../source/thewizardplusplus/wizard_parser/parser/ast_node.hpp"
#include "../../source/thewizardplusplus/wizard_parser/transformers/transformers.hpp"
#include "../vendor/catch/catch.hpp"

TEST_CASE("transformers::join_sequences() function", "[transformers]") {
	using namespace thewizardplusplus::wizard_parser;

	SECTION("without children") {
		const auto type = (+parser::ast_node_type::sequence)._to_string();
		const auto ast = transformers::join_sequences({type, {}, {}});
		CHECK(ast == parser::ast_node{type, {}, {}});
	}

	SECTION("without sequence children") {
		const auto type = (+parser::ast_node_type::sequence)._to_string();
		const auto ast = transformers::join_sequences({type, {}, {
			{"one", "two", {}, 1},
			{"three", "four", {}, 4},
			{"five", "six", {}, 8}
		}});
		CHECK(ast == parser::ast_node{type, {}, {
			{"one", "two", {}, 1},
			{"three", "four", {}, 4},
			{"five", "six", {}, 8}
		}});
	}

	SECTION("with few sequence children") {
		const auto type = (+parser::ast_node_type::sequence)._to_string();
		const auto ast = transformers::join_sequences({type, {}, {
			{"one", "two", {}, 1},
			{type, {}, {}},
			{"three", "four", {}, 4},
			{type, {}, {{"five", "six", {}, 8}}},
			{"seven", "eight", {}, 11},
			{type, {}, {{"nine", "ten", {}, 16}, {"eleven", "twelve", {}, 19}}}
		}});
		CHECK(ast == parser::ast_node{type, {}, {
			{"one", "two", {}, 1},
			{"three", "four", {}, 4},
			{"five", "six", {}, 8},
			{"seven", "eight", {}, 11},
			{"nine", "ten", {}, 16},
			{"eleven", "twelve", {}, 19}
		}});
	}

	SECTION("with a not sequence node at the top level") {
		const auto type = (+parser::ast_node_type::sequence)._to_string();
		const auto ast = transformers::join_sequences({"one", {}, {
			{"two", "three", {}, 1},
			{type, {}, {}},
			{"four", "five", {}, 6},
			{type, {}, {{"six", "seven", {}, 10}}},
			{"eight", "nine", {}, 15},
			{type, {}, {{"ten", "eleven", {}, 19}, {"twelve", "thirteen", {}, 25}}}
		}});
		CHECK(ast == parser::ast_node{"one", {}, {
			{"two", "three", {}, 1},
			{type, {}, {}},
			{"four", "five", {}, 6},
			{type, {}, {{"six", "seven", {}, 10}}},
			{"eight", "nine", {}, 15},
			{type, {}, {{"ten", "eleven", {}, 19}, {"twelve", "thirteen", {}, 25}}}
		}});
	}
}
