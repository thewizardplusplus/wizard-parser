#include "parser/Parser.h"
#include <iostream>

using namespace thewizardplusplus::wizard_parser::parser;

Parser grammar(void) {
	const auto expression = nothing();

	WP_RULE(keywords)
		word(
			"and"_t
			| "break"_t
			| "continue"_t
			| "do"_t
			| "else"_t
			| "end"_t
			| "function"_t
			| "if"_t
			| "include"_t
			| "let"_t
			| "new"_t
			| "not"_t
			| "or"_t
			| "return"_t
			| "structure"_t
			| "then"_t
			| "while"_t
		)
	WP_END

	WP_RULE(number) lexeme(+digit() >> !('.'_s >> +digit())) WP_END
	WP_RULE(identifier) lexeme((letter() | '_'_s) >> *word()) - keywords WP_END
	WP_RULE(string_definition)
		lexeme(
			hide('"'_s)
			>> *(('\\'_s >> any()) | (any() - '"'_s))
			>> hide('"'_s)
		)
	WP_END

	WP_RULE(array_definition)
		hide('['_s) >> !list(expression, hide(','_s)) >> hide(']'_s)
	WP_END
	WP_RULE(atom)
		number
		| identifier
		| array_definition
		| string_definition
		| hide('('_s) >> expression >> hide(')'_s)
	WP_END

	WP_RULE(item_access) hide('['_s) >> expression >> hide(']'_s) WP_END
	WP_RULE(field_access) hide('.'_s) >> identifier WP_END
	WP_RULE(function_call)
		hide('('_s) >> !list(expression, ','_s) >> hide(')'_s)
	WP_END
	WP_RULE(accessor)
		atom >> *(item_access | field_access | function_call)
	WP_END

	WP_RULE(unary) *(word("new"_t) | '-'_s | word("not"_t)) >> accessor WP_END
	WP_RULE(product) list(unary, '*'_s | '/'_s) WP_END
	WP_RULE(sum) list(product, '+'_s | '-'_s) WP_END
	WP_RULE(comparison) list(sum, lexeme(any("<>") >> !'='_s)) WP_END
	WP_RULE(equality) list(comparison, "=="_t | "/="_t) WP_END
	WP_RULE(conjunction) list(equality, hide(word("and"_t))) WP_END
	WP_RULE(disjunction) list(conjunction, hide(word("or"_t))) WP_END
	assign(expression, disjunction);

	return separation(hide(*space()), expression);
}

int main(int number_of_arguments, char* arguments[]) try {
	if (number_of_arguments == 1) {
		throw std::invalid_argument("not specified expression");
	}

	const auto text = arguments[1];
	const auto parser = grammar();
	std::cout
		<< parse(
			parser,
			text,
			SimplifyLevel::AST,
			{"ITEM_ACCESS", "FIELD_ACCESS", "FUNCTION_CALL"}
		)
		<< std::endl;
} catch (std::exception& exception) {
	std::cerr << "Error: \"" << exception.what() << "\"." << std::endl;
	std::exit(EXIT_FAILURE);
}
