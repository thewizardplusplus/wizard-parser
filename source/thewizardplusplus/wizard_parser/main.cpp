#include "parser/Parser.h"
#include <iostream>

using namespace thewizardplusplus::wizard_parser::parser;

Parser grammar(void) {
	const auto expression = nothing();

	const auto number = name(
		"NUMBER",
		lexeme(+digit() >> !('.'_s >> +digit()))
	);
	const auto keywords = word(
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
	);
	const auto identifier = name(
		"IDENTIFIER",
		lexeme((letter() | '_'_s) >> *word()) - keywords
	);
	const auto array_definition = name(
		"ARRAY_DEFINITION",
		'['_s >> !list(expression, hide(','_s)) >> ']'_s
	);
	const auto string_definition = name(
		"STRING_DEFINITION",
		lexeme('"'_s >> *(('\\'_s >> any()) | (any() - '"'_s)) >> '"'_s)
	);
	const auto atom =
		number
		| identifier
		| array_definition
		| string_definition
		| hide('('_s) >> expression >> hide(')'_s);

	const auto item_access = name(
		"ITEM_ACCESS",
		hide('['_s) >> expression >> hide(']'_s)
	);
	const auto field_access = name("FIELD_ACCESS", hide('.'_s) >> identifier);
	const auto function_call = name(
		"FUNCTION_CALL",
		'('_s >> !list(expression, ','_s) >> ')'_s
	);
	const auto accessor = name(
		"ACCESSOR",
		atom >> *(item_access | field_access | function_call)
	);

	const auto unary = name(
		"UNARY",
		*(word("new"_t) | '-'_s | word("not"_t)) >> accessor
	);
	const auto product = name("PRODUCT", list(unary, '*'_s | '/'_s));
	const auto sum = name("SUM", list(product, '+'_s | '-'_s));
	const auto comparison = name(
		"COMPARISON",
		list(sum, '<'_s | "<="_t | '>'_s | ">="_t)
	);
	const auto equality = name("EQUALITY", list(comparison, "=="_t | "/="_t));
	const auto conjunction = name(
		"CONJUNCTION",
		list(equality, hide(word("and"_t)))
	);
	const auto disjunction = name(
		"DISJUNCTION",
		list(conjunction, hide(word("or"_t)))
	);
	assign(expression, disjunction);

	const auto grammar = separation(*space(), expression);
	return grammar;
}

int main(int number_of_arguments, char* arguments[]) try {
	if (number_of_arguments == 1) {
		throw std::invalid_argument("not specified expression");
	}

	const auto text = arguments[1];
	const auto parser = grammar();
	std::cout << parse(parser, text) << std::endl;
} catch (std::exception& exception) {
	std::cerr << "Error: \"" << exception.what() << "\"." << std::endl;
	std::exit(EXIT_FAILURE);
}
