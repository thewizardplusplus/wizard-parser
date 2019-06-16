#define THEWIZARDPLUSPLUS_WIZARD_PARSER_PARSER_MACROSES

#include "vendor/better-enums/enum_strict.hpp"
#include "vendor/range/v3/view/drop.hpp"
#include "vendor/range/v3/view/transform.hpp"
#include "vendor/fmt/format.hpp"
#include "vendor/range/v3/view/chunk.hpp"
#include "vendor/range/v3/to_container.hpp"
#include "vendor/range/v3/numeric/accumulate.hpp"
#include "vendor/docopt/docopt.hpp"
#include "vendor/range/v3/algorithm/find_if.hpp"
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
#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <string_view>
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
  -s, --stdin                          - read an expression from stdin;
  -V, --verbose                        - mark an error.)";
const auto lexemes = lexer::lexeme_group{
	{std::regex{R"(\+)"}, "plus"},
	{std::regex{R"(-)"}, "minus"},
	{std::regex{R"(\*)"}, "star"},
	{std::regex{R"(/)"}, "slash"},
	{std::regex{R"(%)"}, "percent"},
	{std::regex{R"(\()"}, "opening_parenthesis"},
	{std::regex{R"(\))"}, "closing_parenthesis"},
	{std::regex{R"(,)"}, "comma"},
	{std::regex{R"(\d+(\.\d+)?(e-?\d+)?)"}, "number"},
	{std::regex{R"([A-Za-z_]\w*)"}, "identifier"},
	{std::regex{R"(\s+)"}, "whitespace"}
};
const auto lexemes_exceptions = lexer::exception_group{"whitespace"};
// precision is taken from Boost 1.70.0, Math Toolkit 2.9.0
const auto constants = constant_group{
	{"pi", 3.141592653589793238462643383279502884},
	{"e", 2.718281828459045235360287471352662497}
};
const auto functions = std::unordered_map<std::string, function>{
	{"+", {2, [] (const auto& args) { return args[0] + args[1]; }}},
	{"-", {2, [] (const auto& args) { return args[0] - args[1]; }}},
	{"*", {2, [] (const auto& args) { return args[0] * args[1]; }}},
	{"/", {2, [] (const auto& args) { return args[0] / args[1]; }}},
	{"%", {2, [] (const auto& args) { return std::fmod(args[0], args[1]); }}},
	{"floor", {1, [] (const auto& args) { return std::floor(args[0]); }}},
	{"ceil", {1, [] (const auto& args) { return std::ceil(args[0]); }}},
	{"trunc", {1, [] (const auto& args) { return std::trunc(args[0]); }}},
	{"round", {1, [] (const auto& args) { return std::round(args[0]); }}},
	{"sin", {1, [] (const auto& args) { return std::sin(args[0]); }}},
	{"cos", {1, [] (const auto& args) { return std::cos(args[0]); }}},
	{"tn", {1, [] (const auto& args) { return std::tan(args[0]); }}},
	{"arcsin", {1, [] (const auto& args) { return std::asin(args[0]); }}},
	{"arccos", {1, [] (const auto& args) { return std::acos(args[0]); }}},
	{"arctn", {1, [] (const auto& args) { return std::atan(args[0]); }}},
	{"angle", {2, [] (const auto& args) { return std::atan2(args[1], args[0]); }}},
	{"pow", {2, [] (const auto& args) { return std::pow(args[0], args[1]); }}},
	{"sqrt", {1, [] (const auto& args) { return std::sqrt(args[0]); }}},
	{"exp", {1, [] (const auto& args) { return std::exp(args[0]); }}},
	{"ln", {1, [] (const auto& args) { return std::log(args[0]); }}},
	{"lg", {1, [] (const auto& args) { return std::log10(args[0]); }}},
	{"abs", {1, [] (const auto& args) { return std::abs(args[0]); }}},
};

template<typename streamable>
void exit(const int& code, const streamable& message) {
	(code == EXIT_SUCCESS ? std::cout : std::cerr) << message << '\n';
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

double evaluate_ast_node(
	const parser::ast_node& ast,
	const constant_group& constants,
	const std::unordered_map<std::string, function>& functions
) {
	const auto inspect_sequence = [] (const auto& ast) -> const auto& {
		return ast.children[0].children;
	};
	const auto evaluate_with_context = [&] (const auto& ast) {
		return evaluate_ast_node(ast, constants, functions);
	};

	if (ast.type == "number") {
		return std::stod(ast.value, nullptr);
	} else if (ast.type == "identifier") {
		try {
			return constants.at(ast.value);
		} catch (const std::out_of_range& exception) {
			const auto offset = parser::get_offset(ast);
			throw unexpected_entity_exception<entity_type::constant>{offset};
		}
	} else if (ast.type == "atom") {
		const auto type = (+parser::ast_node_type::sequence)._to_string();
		const auto first_child = ast.children[0].type == type
			? inspect_sequence(ast)[0]
			: ast.children[0];
		return evaluate_with_context(first_child);
	} else if (ast.type == "unary") {
		const auto result = evaluate_with_context(inspect_sequence(ast).back());
		const auto sign = (inspect_sequence(ast).size() - 1) % 2 ? -1 : 1;
		return sign * result;
	} else if (ast.type == "function_call") {
		try {
			const auto name = inspect_sequence(ast)[0].value;
			const auto arguments = inspect_sequence(ast)
				| ranges::view::drop(1)
				| ranges::view::transform([&] (const auto& ast) {
					return evaluate_with_context(ast);
				});
			const auto function = functions.at(name);
			if (arguments.size() != function.arity) {
				const auto unit = function.arity == 1 ? "argument" : "arguments";
				const auto description =
					fmt::format("function requires {:d} {:s}", function.arity, unit);
				const auto offset = parser::get_offset(ast);
				throw exceptions::positional_exception{description, offset};
			}

			return function.handler(arguments);
		} catch (const std::out_of_range& exception) {
			const auto offset = parser::get_offset(ast);
			throw unexpected_entity_exception<entity_type::function>{offset};
		}
	} else if (ast.type == "product" || ast.type == "sum") {
		const auto first_operand = evaluate_with_context(inspect_sequence(ast)[0]);
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
				const auto name = chunk[0].value;
				const auto second_operand = evaluate_with_context(chunk[1]);
				return functions.at(name).handler({result, second_operand});
			}
		);
	} else {
		const auto offset = parser::get_offset(ast);
		throw unexpected_entity_exception<entity_type::node>{offset};
	}
}

std::runtime_error enrich_exception(
	const exceptions::positional_exception& exception,
	const std::string_view& code,
	const std::size_t& mark_length
) {
	const auto mark_offset = std::string(exception.offset, ' ');
	const auto mark = std::string(mark_length, '^');
	return std::runtime_error{fmt::format(
		"{:s}\n| \"{:s}\"\n|  {:s}{:s}",
		exception.what(),
		code,
		mark_offset,
		mark
	)};
}

int main(int argc, char* argv[]) try {
	const auto options = docopt::docopt(usage, {argv+1, argv+argc}, true);
	const auto expression = options.at("<expression>")
		? options.at("<expression>").asString()
		: "";
	const auto code = options.at("--stdin").asBool()
		? std::string{std::istreambuf_iterator<char>{std::cin}, {}}
		: expression;
	const auto enrich = options.at("--verbose").asBool()
		? std::function{enrich_exception}
		: [] (
			const exceptions::positional_exception& exception,
			const std::string_view& code,
			const std::size_t& mark_length
		) { return exception; };
	try {
		auto tokens = lexer::tokenize_all(lexemes, lexemes_exceptions, code);
		if (options.at("--target") == "tokens"s) {
			exit(EXIT_SUCCESS, tokens);
		}

		const auto eoi = exceptions::entity_type::eoi;
		try {
			const auto ast = parser::parse_all(make_parser(), tokens);
			if (options.at("--target") == "cst"s) {
				exit(EXIT_SUCCESS, ast);
			}

			auto buffer = std::ostringstream{};
			const auto precision = options.at("--precision")
				? options.at("--precision").asLong()
				: std::numeric_limits<double>::max_digits10;
			const auto result = evaluate_ast_node(ast, constants, functions);
			buffer << std::setprecision(precision) << result;

			exit(EXIT_SUCCESS, buffer.str());
		} catch (const exceptions::unexpected_entity_exception<eoi>& exception) {
			const auto offset = exception.offset == utilities::integral_infinity
				? code.size()
				: exception.offset;
			throw exceptions::unexpected_entity_exception<eoi>{offset};
		} catch (const exceptions::positional_exception& exception) {
			const auto token = ranges::find_if(tokens, [&] (const auto& token) {
				return token.offset == exception.offset;
			});
			throw enrich(exception, code, token->value.size());
		}
	} catch (const exceptions::positional_exception& exception) {
		throw enrich(exception, code, 1);
	}
} catch (const std::exception& exception) {
	exit(EXIT_FAILURE, fmt::format("error: {:s}", exception.what()));
}
