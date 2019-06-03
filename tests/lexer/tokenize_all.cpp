#include "../../source/thewizardplusplus/wizard_parser/lexer/token.hpp"
#include "../../source/thewizardplusplus/wizard_parser/lexer/tokenize.hpp"
#include "../../source/thewizardplusplus/wizard_parser/exceptions/unexpected_entity_exception.hpp"
#include "../vendor/catch/catch.hpp"
#include <optional>
#include <regex>

TEST_CASE("lexer::tokenize_all() function", "[lexer]") {
	using namespace thewizardplusplus::wizard_parser;

	SECTION("without rest") {
		auto tokens = std::optional<lexer::token_group>{};
		const auto call = [&] {
			tokens = lexer::tokenize_all(
				{
					{std::regex{"[[:alpha:]]+"}, "alpha"},
					{std::regex{"[[:digit:]]+"}, "digit"},
					{std::regex{"[[:space:]]+"}, "space"}
				},
				{},
				"test 23"
			);
		};
		CHECK_NOTHROW(call());
		REQUIRE(tokens.has_value());
		CHECK(*tokens == lexer::token_group{
			{"alpha", "test", {}},
			{"space", " ", 4},
			{"digit", "23", 5}
		});
	}

	SECTION("with rest") {
		const auto type = exceptions::entity_type::symbol;
		auto tokens = std::optional<lexer::token_group>{};
		const auto call = [&] {
			tokens = lexer::tokenize_all(
				{
					{std::regex{"[[:alpha:]]+"}, "alpha"},
					{std::regex{"[[:digit:]]+"}, "digit"},
					{std::regex{"[[:space:]]+"}, "space"}
				},
				{},
				"test #23"
			);
		};
		CHECK_THROWS_AS(call(), exceptions::unexpected_entity_exception<type>);
		CHECK(!tokens.has_value());
	}

	SECTION("without matches") {
		const auto type = exceptions::entity_type::symbol;
		auto tokens = std::optional<lexer::token_group>{};
		const auto call = [&] {
			tokens = lexer::tokenize_all(
				{
					{std::regex{"[[:alpha:]]+"}, "alpha"},
					{std::regex{"[[:digit:]]+"}, "digit"},
					{std::regex{"[[:space:]]+"}, "space"}
				},
				{},
				"#"
			);
		};
		CHECK_THROWS_AS(call(), exceptions::unexpected_entity_exception<type>);
		CHECK(!tokens.has_value());
	}
}
