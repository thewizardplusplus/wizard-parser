#include "../../source/thewizardplusplus/wizard_parser/parser/ast_node.hpp"
#include "../../source/thewizardplusplus/wizard_parser/transformers/transform.hpp"
#include "../../source/thewizardplusplus/wizard_parser/transformers/transformers.hpp"
#include "../vendor/catch/catch.hpp"

TEST_CASE("transformers::transform() function for few handlers", "[transformers]") {
	using namespace thewizardplusplus::wizard_parser;

	SECTION("without handlers") {
		const auto sequence_type = (+parser::ast_node_type::sequence)._to_string();
		const auto nothing_type = (+parser::ast_node_type::nothing)._to_string();
		const auto ast = parser::ast_node{sequence_type, {}, {
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
		}};

		const auto transformed_ast = transformers::transform(
			ast,
			transformers::ast_node_handler_group{}
		);
		CHECK(transformed_ast == parser::ast_node{sequence_type, {}, {
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
	}

	SECTION("with any handlers") {
		const auto sequence_type = (+parser::ast_node_type::sequence)._to_string();
		const auto nothing_type = (+parser::ast_node_type::nothing)._to_string();
		const auto ast = parser::ast_node{sequence_type, {}, {
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
		}};

		const auto transformed_ast = transformers::transform(
			ast,
			transformers::ast_node_handler_group{transformers::join_sequences}
		);
		CHECK(transformed_ast == parser::ast_node{sequence_type, {}, {
			parser::ast_node{"identifier", "one", {}, 1},
			parser::ast_node{nothing_type, {}, {}, 4},
			parser::ast_node{"identifier", "two", {}, 5},
			parser::ast_node{nothing_type, {}, {}, 8},
			parser::ast_node{"identifier", "three", {}, 9}
		}});
	}

	SECTION("with default handlers") {
		const auto sequence_type = (+parser::ast_node_type::sequence)._to_string();
		const auto nothing_type = (+parser::ast_node_type::nothing)._to_string();
		const auto ast = parser::ast_node{sequence_type, {}, {
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
		}};

		const auto transformed_ast = transformers::transform(ast);
		CHECK(transformed_ast == parser::ast_node{sequence_type, {}, {
			parser::ast_node{"identifier", "one", {}, 1},
			parser::ast_node{"identifier", "two", {}, 5},
			parser::ast_node{"identifier", "three", {}, 9}
		}});
	}
}
