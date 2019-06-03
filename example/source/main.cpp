#define THEWIZARDPLUSPLUS_WIZARD_PARSER_PARSER_MACROSES

#include "vendor/better-enums/enum_strict.hpp"
#include "vendor/range/v3/view/drop.hpp"
#include "vendor/range/v3/view/transform.hpp"
#include "vendor/fmt/format.hpp"
#include "vendor/range/v3/view/chunk.hpp"
#include "vendor/range/v3/to_container.hpp"
#include "vendor/range/v3/numeric/accumulate.hpp"
#include "vendor/docopt/docopt.hpp"
#include <thewizardplusplus/wizard_parser/exceptions/unexpected_entity_exception.hpp>
#include <thewizardplusplus/wizard_parser/lexer/lexeme.hpp>
#include <thewizardplusplus/wizard_parser/lexer/tokenize.hpp>
#include <thewizardplusplus/wizard_parser/parser/rule_parser.hpp>
#include <thewizardplusplus/wizard_parser/parser/dummy_parser.hpp>
#include <thewizardplusplus/wizard_parser/parser/typing_parser.hpp>
#include <thewizardplusplus/wizard_parser/parser/match_parser.hpp>
#include <thewizardplusplus/wizard_parser/parser/concatenation_parser.hpp>
#include <thewizardplusplus/wizard_parser/parser/lookahead_parser.hpp>
#include <thewizardplusplus/wizard_parser/parser/repetition_parser.hpp>
#include <thewizardplusplus/wizard_parser/parser/alternation_parser.hpp>
#include <thewizardplusplus/wizard_parser/parser/ast_node.hpp>
#include <thewizardplusplus/wizard_parser/exceptions/positional_exception.hpp>
#include <thewizardplusplus/wizard_parser/parser/parse.hpp>
#include <thewizardplusplus/wizard_parser/utilities/utilities.hpp>
#include <unordered_map>
#include <string>
#include <cstddef>
#include <functional>
#include <vector>
#include <cstdint>
#include <regex>
#include <iostream>
#include <cstdlib>
#include <iterator>
#include <sstream>
#include <limits>
#include <iomanip>
#include <exception>

using namespace thewizardplusplus::wizard_parser;
using namespace thewizardplusplus::wizard_parser::parser::operators;
using namespace std::literals::string_literals;

using constant_group = std::unordered_map<std::string, double>;

struct function final {
	const std::size_t arity;
	const std::function<double(const std::vector<double>&)> handler;
};

using function_group = std::unordered_map<std::string, function>;

BETTER_ENUM(entity_type, std::uint8_t,
	node = exceptions::entity_type::_size(),
	constant,
	function
)

template<entity_type::_integral type>
using unexpected_entity_exception =
	exceptions::base_unexpected_entity_exception<entity_type, type>;

const auto usage =
R"(Usage:
  ./example [options] [--] [<expression>]

Options:
  -h, --help                           - show this message;
  -t TARGET, --target TARGET           - preliminary target of processing
                                       (allowed: tokens, cst);
  -p PRECISION, --precision PRECISION  - precision of a result;
  -s, --stdin                          - read an expression from stdin.)";
const auto lexemes = lexer::lexeme_group{
	{std::regex{R"(\+)"}, "plus"},
	{std::regex{"-"}, "minus"},
	{std::regex{R"(\*)"}, "star"},
	{std::regex{"/"}, "slash"},
	{std::regex{"%"}, "percent"},
	{std::regex{R"(\()"}, "opening_parenthesis"},
	{std::regex{R"(\))"}, "closing_parenthesis"},
	{std::regex{","}, "comma"},
	{std::regex{R"(\d+(?:\.\d+)?(?:e-?\d+)?)"}, "number"},
	{std::regex{R"([A-Za-z_]\w*)"}, "identifier"},
	{std::regex{R"(\s+)"}, "whitespace"}
};
const auto lexemes_exceptions = lexer::exception_group{"whitespace"};
// Boost 1.70.0, Math Toolkit 2.9.0
const auto constants = constant_group{
	{"pi", 3.141592653589793238462643383279502884},
	{"e", 2.718281828459045235360287471352662497}
};
const auto functions = function_group{
	{"+", {2, [] (const auto& arguments) {
		return arguments.front() + arguments.back();
	}}},
	{"-", {2, [] (const auto& arguments) {
		return arguments.front() - arguments.back();
	}}},
	{"*", {2, [] (const auto& arguments) {
		return arguments.front() * arguments.back();
	}}},
	{"/", {2, [] (const auto& arguments) {
		return arguments.front() / arguments.back();
	}}},
	{"%", {2, [] (const auto& arguments) {
		return static_cast<std::int64_t>(arguments.front())
			% static_cast<std::int64_t>(arguments.back());
	}}},
	{"floor", {1, [] (const auto& arguments) {
		return std::floor(arguments.front());
	}}},
	{"ceil", {1, [] (const auto& arguments) {
		return std::ceil(arguments.front());
	}}},
	{"trunc", {1, [] (const auto& arguments) {
		return std::trunc(arguments.front());
	}}},
	{"round", {1, [] (const auto& arguments) {
		return std::round(arguments.front());
	}}},
	{"sin", {1, [] (const auto& arguments) {
		return std::sin(arguments.front());
	}}},
	{"cos", {1, [] (const auto& arguments) {
		return std::cos(arguments.front());
	}}},
	{"tn", {1, [] (const auto& arguments) {
		return std::tan(arguments.front());
	}}},
	{"arcsin", {1, [] (const auto& arguments) {
		return std::asin(arguments.front());
	}}},
	{"arccos", {1, [] (const auto& arguments) {
		return std::acos(arguments.front());
	}}},
	{"arctn", {1, [] (const auto& arguments) {
		return std::atan(arguments.front());
	}}},
	{"angle", {2, [] (const auto& arguments) {
		return std::atan2(arguments.back(), arguments.front());
	}}},
	{"pow", {2, [] (const auto& arguments) {
		return std::pow(arguments.front(), arguments.back());
	}}},
	{"sqrt", {1, [] (const auto& arguments) {
		return std::sqrt(arguments.front());
	}}},
	{"exp", {1, [] (const auto& arguments) {
		return std::exp(arguments.front());
	}}},
	{"ln", {1, [] (const auto& arguments) {
		return std::log(arguments.front());
	}}},
	{"lg", {1, [] (const auto& arguments) {
		return std::log10(arguments.front());
	}}},
	{"abs", {1, [] (const auto& arguments) {
		return std::abs(arguments.front());
	}}},
};

template<typename streamable>
void stop(const int& code, std::ostream& stream, const streamable& message) {
	stream << message << '\n';
	std::exit(code);
}

parser::rule_parser::pointer make_parser() {
	const auto expression_dummy = parser::dummy();
	RULE(function_call) = "identifier"_t >> &"("_v >>
		-(expression_dummy >> *(&","_v >> expression_dummy))
	>> &")"_v;
	RULE(atom) = "number"_t
		| function_call
		| "identifier"_t
		| (&"("_v >> expression_dummy >> &")"_v);
	RULE(unary) = *("-"_v) >> atom;
	RULE(product) = unary >> *(("*"_v | "/"_v | "%"_v) >> unary);
	RULE(sum) = product >> *(("+"_v | "-"_v) >> product);
	expression_dummy->set_parser(sum);

	return sum;
}

const parser::ast_node_group& inspect_sequence(const parser::ast_node& ast) {
	return ast.children.front().children;
}

double evaluate_ast_node(
	const parser::ast_node& ast,
	const constant_group& constants,
	const function_group& functions
) {
	const auto evaluate_with_context = [&] (const auto& ast) {
		return evaluate_ast_node(ast, constants, functions);
	};

	if (ast.type == "number") {
		return std::stod(ast.value, nullptr);
	} else if (ast.type == "identifier") {
		try {
			return constants.at(ast.value);
		} catch (const std::out_of_range& exception) {
			throw unexpected_entity_exception<entity_type::constant>{
				parser::get_offset(ast)
			};
		}
	} else if (ast.type == "atom") {
		const auto type = (+parser::ast_node_type::sequence)._to_string();
		const auto first_child = ast.children.front().type == type
			? inspect_sequence(ast).front()
			: ast.children.front();
		return evaluate_with_context(first_child);
	} else if (ast.type == "unary") {
		const auto result = evaluate_with_context(inspect_sequence(ast).back());
		const auto sign = (inspect_sequence(ast).size()-1) % 2 ? -1 : 1;
		return sign * result;
	} else if (ast.type == "function_call") {
		try {
			const auto name = inspect_sequence(ast).front().value;
			const auto arguments = inspect_sequence(ast)
				| ranges::view::drop(1)
				| ranges::view::transform([&] (const auto& ast) {
					return evaluate_with_context(ast);
				});
			const auto function = functions.at(name);
			if (arguments.size() != function.arity) {
				throw exceptions::positional_exception{
					fmt::format(
						"function requires {:d} {:s}",
						function.arity,
						function.arity == 1 ? "argument" : "arguments"
					),
					parser::get_offset(ast)
				};
			}

			return function.handler(arguments);
		} catch (const std::out_of_range& exception) {
			throw unexpected_entity_exception<entity_type::function>{
				parser::get_offset(ast)
			};
		}
	} else if (ast.type == "product" || ast.type == "sum") {
		const auto first_operand =
			evaluate_with_context(inspect_sequence(ast).front());
		const auto children_chunks = inspect_sequence(ast)
			| ranges::view::drop(1)
			| ranges::view::chunk(2)
			| ranges::view::transform([] (const auto& chunk) {
				return chunk | ranges::to_<parser::ast_node_group>();
			});
		return ranges::accumulate(
			children_chunks,
			first_operand,
			[&] (const auto& result, const auto& chunk) {
				const auto name = chunk.front().value;
				const auto second_operand = evaluate_with_context(chunk.back());
				return functions.at(name).handler({result, second_operand});
			}
		);
	} else {
		throw unexpected_entity_exception<entity_type::node>{parser::get_offset(ast)};
	}
}

int main(int argc, char* argv[]) try {
	const auto options = docopt::docopt(usage, {argv+1, argv+argc}, true);
	const auto expression = options.at("<expression>")
		? options.at("<expression>").asString()
		: "";
	const auto code = options.at("--stdin").asBool()
		? std::string{std::istreambuf_iterator<char>{std::cin}, {}}
		: expression;
	auto tokens = lexer::tokenize_all(lexemes, lexemes_exceptions, code);
	if (options.at("--target") == "tokens"s) {
		stop(EXIT_SUCCESS, std::cout, tokens);
	}

	try {
		const auto ast = parser::parse_all(make_parser(), tokens);
		if (options.at("--target") == "cst"s) {
			stop(EXIT_SUCCESS, std::cout, ast);
		}

		auto buffer = std::ostringstream{};
		const auto precision = options.at("--precision")
			? options.at("--precision").asLong()
			: std::numeric_limits<double>::max_digits10;
		const auto result = evaluate_ast_node(ast, constants, functions);
		buffer << std::setprecision(precision) << result;

		stop(EXIT_SUCCESS, std::cout, buffer.str());
	} catch (const exceptions::positional_exception& exception) {
		const auto offset = exception.offset == utilities::integral_infinity
			? code.size()
			: exception.offset;
		throw exceptions::positional_exception{exception.description, offset};
	}
} catch (const std::exception& exception) {
	stop(EXIT_FAILURE, std::cerr, fmt::format("error: {:s}", exception.what()));
}
