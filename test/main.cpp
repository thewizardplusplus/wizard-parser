#include <wizard_parser/parser/Parser.h>
#include <iostream>

using namespace thewizardplusplus::wizard_parser::parser;

/* Grammar description in EBNF:
 *
 * expression = disjunction;
 * disjunction = conjunction, {"or", conjunction};
 * conjunction = equality, {"and", equality};
 * equality = comparison, {("==" | "/="), comparison};
 * comparison = sum, {("<" | "<=" | ">" | ">="), sum};
 * sum = product, {("+" | "-"), product};
 * product = unary, {("*" | "/"), unary};
 * unary = {"new" | "-" | "not"}, atom;
 * atom = number | ("(", expression, ")");
 * number = ? /\d+(\.\d+)?/ ?;
 */
Parser grammar(void) {
	const auto expression = dummy();

	WP_RULE(number)
		disable_separation(lexeme(+digit() >> !('.'_s >> +digit())))
	WP_END
	WP_RULE(atom) number | hide('('_s) >> expression >> hide(')'_s) WP_END
	WP_RULE(unary) *(word("new"_t) | '-'_s | word("not"_t)) >> atom WP_END
	WP_RULE(product) list(unary, '*'_s | '/'_s) WP_END
	WP_RULE(sum) list(product, '+'_s | '-'_s) WP_END
	WP_RULE(comparison) list(sum, '<'_s | "<="_t | '>'_s | ">="_t) WP_END
	WP_RULE(equality) list(comparison, "=="_t | "/="_t) WP_END
	WP_RULE(conjunction) list(equality, hide(word("and"_t))) WP_END
	WP_RULE(disjunction) list(conjunction, hide(word("or"_t))) WP_END
	assign(expression, disjunction);

	return separation(hide(*space()), expression >> end());
}

int main(int number_of_arguments, char* arguments[]) try {
	if (number_of_arguments == 1) {
		throw std::invalid_argument("not specified expression");
	}

	const auto text = arguments[1];
	const auto parser = grammar();
	std::cout
		<< "<?xml version = \"1.0\" encoding = \"utf-8\" ?>"
		<< parse(parser, text, SimplifyLevel::AST)
		<< std::endl;
} catch (std::exception& exception) {
	std::cerr << "Error: \"" << exception.what() << "\"." << std::endl;
	std::exit(EXIT_FAILURE);
}
