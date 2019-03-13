#include "../../source/thewizardplusplus/wizard_parser/lexer/token.hpp"
#include "../../source/thewizardplusplus/wizard_parser/parser/rule_parser.hpp"
#include "../../source/thewizardplusplus/wizard_parser/parser/ast_node.hpp"
#include "../../source/thewizardplusplus/wizard_parser/parser/dummy_parser.hpp"
#include "../vendor/catch/catch.hpp"
#include "../vendor/fakeit/fakeit.hpp"

TEST_CASE("parser::dummy_parser class", "[parser]") {
	using namespace thewizardplusplus::wizard_parser;

	auto tokens = lexer::token_group{{"one", "two", 1}, {"three", "four", 4}};
	auto mock_parser = fakeit::Mock<parser::rule_parser>{};
	fakeit::When(Method(mock_parser, parse))
		.Return(parser::parsing_result{
			parser::ast_node{"one", "two", {}, 1},
			lexer::token_span{tokens}.subspan(1)
		});
	fakeit::Fake(Dtor(mock_parser));

	const auto mock_parser_pointer =
		parser::rule_parser::pointer{&mock_parser.get()};
	const auto dummy_parser = parser::dummy();
	dummy_parser->set_parser(mock_parser_pointer);

	const auto [ast, rest_tokens] = dummy_parser->parse(tokens);
	REQUIRE(ast.has_value());
	CHECK(*ast == parser::ast_node{"one", "two", {}, 1});
	CHECK(rest_tokens == lexer::token_span{tokens}.subspan(1));

	fakeit::Verify(Method(mock_parser, parse)).Once();
}
