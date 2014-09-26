#include "parser/Parser.h"
#include <iostream>

using namespace thewizardplusplus::wizard_parser::parser;

Parser grammar(void) {
	const auto expression = nothing();
	const auto statement_list_copy = nothing();

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

	WP_RULE(number)
		separation(nothing(), lexeme(+digit() >> !('.'_s >> +digit())))
	WP_END
	WP_RULE(identifier)
		separation(nothing(), lexeme((letter() | '_'_s) >> *word()) - keywords)
	WP_END
	WP_RULE(string_definition)
		lexeme(
			separation(
				nothing(),
				hide('"'_s)
					>> *(('\\'_s >> any()) | (any() - '"'_s))
					>> hide('"'_s)
			)
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

	WP_RULE(variable_definition)
		hide(word("let"_t)) >> identifier >> '='_s >> expression
	WP_END
	WP_RULE(assignment) expression >> '='_s >> expression WP_END
	WP_RULE(condition)
		hide(word("if"_t)) >> expression >> hide(word("then"_t))
			>> statement_list_copy
		>> *(hide(word("else"_t))
			>> hide(word("if"_t))
			>> expression
			>> hide(word("then"_t))
			>> statement_list_copy)
		>> !(hide(word("else"_t))
			>> statement_list_copy)
		>> hide(word("end"_t))
	WP_END
	WP_RULE(loop)
		hide(word("while"_t)) >> expression >> hide(word("do"_t))
			>> statement_list_copy
		>> hide(word("end"_t))
	WP_END
	WP_RULE(loop_continue) hide(word("continue"_t)) WP_END
	WP_RULE(loop_break) hide(word("break"_t)) WP_END
	WP_RULE(function_return)
		hide(word("return"_t)) >> !expression
	WP_END

	WP_RULE(statement)
		variable_definition
		| assignment
		| condition
		| loop
		| loop_continue
		| loop_break
		| function_return
		| expression
	WP_END
	WP_RULE(statement_list) +statement WP_END
	assign(statement_list_copy, statement_list);

	WP_RULE(structure_declaration)
		hide(word("structure"_t)) >> identifier
			>> +identifier
		>> hide(word("end"_t))
	WP_END
	WP_RULE(function_declaration)
		hide(word("function"_t))
			>> identifier
			>> hide('('_s)
			>> !list(identifier, hide(','_s))
			>> hide(')'_s)
			>> statement_list_copy
		>> hide(word("end"_t))
	WP_END

	WP_RULE(program)
		variable_definition
		| structure_declaration
		| function_declaration
	WP_END

	return separation(hide(*space()), program);
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
			{
				"item_access",
				"field_access",
				"function_call",
				"function_return",
				"statement_list"
			}
		)
		<< std::endl;
} catch (std::exception& exception) {
	std::cerr << "Error: \"" << exception.what() << "\"." << std::endl;
	std::exit(EXIT_FAILURE);
}
