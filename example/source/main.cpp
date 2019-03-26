#define THEWIZARDPLUSPLUS_WIZARD_PARSER_PARSER_MACROSES

#include "vendor/better-enums/enum_strict.hpp"
#include "vendor/fmt/format.hpp"
#include "vendor/range/v3/view/filter.hpp"
#include "vendor/range/v3/to_container.hpp"
#include "vendor/range/v3/view/transform.hpp"
#include "vendor/range/v3/view/join.hpp"
#include "vendor/range/v3/view/drop.hpp"
#include "vendor/range/v3/view/chunk.hpp"
#include "vendor/docopt/docopt.hpp"
#include "vendor/json.hpp"
#include "vendor/range/v3/numeric/accumulate.hpp"
#include "vendor/range/v3/view/concat.hpp"
#include "vendor/range/v3/view/single.hpp"
#include <thewizardplusplus/wizard_parser/parser/ast_node.hpp>
#include <thewizardplusplus/wizard_parser/lexer/lexeme.hpp>
#include <thewizardplusplus/wizard_parser/parser/rule_parser.hpp>
#include <thewizardplusplus/wizard_parser/parser/dummy_parser.hpp>
#include <thewizardplusplus/wizard_parser/parser/typing_parser.hpp>
#include <thewizardplusplus/wizard_parser/parser/match_parser.hpp>
#include <thewizardplusplus/wizard_parser/parser/concatenation_parser.hpp>
#include <thewizardplusplus/wizard_parser/parser/lookahead_parser.hpp>
#include <thewizardplusplus/wizard_parser/parser/repetition_parser.hpp>
#include <thewizardplusplus/wizard_parser/parser/alternation_parser.hpp>
#include <thewizardplusplus/wizard_parser/lexer/tokenize.hpp>
#include <thewizardplusplus/wizard_parser/lexer/token.hpp>
#include <thewizardplusplus/wizard_parser/utilities/utilities.hpp>
#include <functional>
#include <unordered_map>
#include <string>
#include <cstddef>
#include <vector>
#include <cstdint>
#include <stdexcept>
#include <regex>
#include <iostream>
#include <cstdlib>
#include <iterator>
#include <exception>

using namespace thewizardplusplus::wizard_parser;
using namespace thewizardplusplus::wizard_parser::parser::operators;
using namespace std::literals::string_literals;

using ast_node_handler =
	std::function<parser::ast_node(const parser::ast_node&)>;

using constant_group = std::unordered_map<std::string, double>;

struct function final {
	const std::size_t arity;
	const std::function<double(const std::vector<double>&)> handler;
};

using function_group = std::unordered_map<std::string, function>;

BETTER_ENUM(entity_type, std::uint8_t,
	symbol,
	token,
	eoi,
	node,
	constant,
	function
)

template<entity_type::_integral type>
struct unexpected_entity_exception final: std::runtime_error {
	static_assert(entity_type::_is_valid(type));

	explicit unexpected_entity_exception(const std::size_t& offset);
};

template<entity_type::_integral type>
unexpected_entity_exception<type>::unexpected_entity_exception(
	const std::size_t& offset
):
	std::runtime_error{fmt::format(
		"unexpected {:s} (offset: {:d})",
		entity_type::_from_integral(type)._to_string(),
		offset
	)}
{}

const auto usage =
R"(Usage:
  ./example -h | --help
  ./example [-t TARGET | --target TARGET] [--] <expression>
  ./example [-t TARGET | --target TARGET] (-s | --stdin)

Options:
  -h, --help                  - show this message;
  -t TARGET, --target TARGET  - preliminary target of processing
                              (allowed: tokens, cst);
  -s, --stdin                 - read an expression from stdin.)";
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
const auto handlers = std::vector<ast_node_handler>{
	// remove CST nodes with the nothing type
	[] (const auto& ast) {
		const auto type = (+parser::ast_node_type::nothing)._to_string();
		const auto new_children = ast.children
			| ranges::view::filter([&] (const auto& ast) { return ast.type != type; })
			| ranges::to_<parser::ast_node_group>();
		return parser::ast_node{ast.type, ast.value, new_children, ast.offset};
	},
	// join CST nodes with the sequence type
	[] (const auto& ast) {
		const auto type = (+parser::ast_node_type::sequence)._to_string();
		if (ast.type != type) {
			return ast;
		}

		const auto new_children_set = ast.children
			| ranges::view::transform([&] (const auto& ast) {
				return ast.type == type ? ast.children : parser::ast_node_group{ast};
			})
			| ranges::to_<std::vector<parser::ast_node_group>>();
		const auto new_children = new_children_set
			| ranges::view::join
			| ranges::to_<parser::ast_node_group>();
		return parser::ast_node{ast.type, ast.value, new_children, ast.offset};
	}
};
const auto constants = constant_group{
	{"pi", 3.1415926535897932384626433},
	{"e", 2.7182818284590452353602874}
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

void stop(const int& code, std::ostream& stream, const std::string& message) {
	stream << fmt::format("{:s}\n", message);
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

parser::ast_node walk_ast_node(
	const parser::ast_node& ast,
	const ast_node_handler& handler
) {
	const auto new_children = ast.children
		| ranges::view::transform([&] (const auto& ast) {
			return walk_ast_node(ast, handler);
		});
	return handler({ast.type, ast.value, new_children, ast.offset});
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
			throw unexpected_entity_exception<entity_type::constant>{*ast.offset};
		}
	} else if (ast.type == "atom") {
		const auto type = (+parser::ast_node_type::sequence)._to_string();
		const auto first_child = ast.children.front().type == type
			? ast.children.front().children.front()
			: ast.children.front();
		return evaluate_with_context(first_child);
	} else if (ast.type == "unary") {
		const auto children = ast.children.front().children;
		const auto result = evaluate_with_context(children.back());
		const auto sign = (children.size()-1) % 2 ? -1 : 1;
		return sign * result;
	} else if (ast.type == "function_call") {
		try {
			const auto children = ast.children.front().children;
			const auto name = children.front().value;
			const auto arguments = children
				| ranges::view::drop(1)
				| ranges::view::transform([&] (const auto& ast) {
					return evaluate_with_context(ast);
				});
			const auto function = functions.at(name);
			if (arguments.size() != function.arity) {
				throw std::runtime_error(fmt::format(
					"function {}() requires {} arguments",
					name,
					function.arity
				));
			}

			return function.handler(arguments);
		} catch (const std::out_of_range& exception) {
			throw unexpected_entity_exception<entity_type::function>{
				utilities::integral_infinity
			};
		}
	} else if (ast.type == "product" || ast.type == "sum") {
		const auto children = ast.children.front().children;
		const auto first_operand = evaluate_with_context(children.front());
		const auto children_chunks = children
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
		throw unexpected_entity_exception<entity_type::node>{
			utilities::integral_infinity
		};
	}
}

int main(int argc, char* argv[]) try {
	const auto options = docopt::docopt(usage, {argv+1, argv+argc}, true);
	const auto code = options.at("--stdin").asBool()
		? std::string{std::istreambuf_iterator<char>{std::cin}, {}}
		: options.at("<expression>").asString();
	const auto [tokens, rest_offset] = lexer::tokenize(lexemes, code);
	if (rest_offset != code.size()) {
		throw unexpected_entity_exception<entity_type::symbol>{rest_offset};
	}

	auto cleaned_tokens = tokens
		| ranges::view::filter([] (const auto& token) {
			return token.type != "whitespace";
		})
		| ranges::to_<lexer::token_group>();
	if (options.at("--target") == "tokens"s) {
		stop(EXIT_SUCCESS, std::cout, nlohmann::json(cleaned_tokens).dump());
	}

	const auto ast = make_parser()->parse(cleaned_tokens);
	if (!ast.rest_tokens.empty()) {
		throw unexpected_entity_exception<entity_type::token>{
			lexer::get_offset(ast.rest_tokens)
		};
	}
	if (!ast.node) {
		throw unexpected_entity_exception<entity_type::eoi>{code.size()};
	}

	const auto completed_handlers = ranges::view::concat(
		// replace CST nodes offsets which are equal
		// to the utilities::integral_infinity constant to a code size
		ranges::view::single([&] (const auto& ast) {
			const auto offset = ast.offset == utilities::integral_infinity
				? code.size()
				: ast.offset;
			return parser::ast_node{ast.type, ast.value, ast.children, offset};
		}),
		handlers
	);
	const auto transformed_ast = ranges::accumulate(
		completed_handlers,
		*ast.node,
		walk_ast_node
	);
	if (options.at("--target") == "cst"s) {
		stop(EXIT_SUCCESS, std::cout, nlohmann::json(transformed_ast).dump());
	}

	const auto result = evaluate_ast_node(transformed_ast, constants, functions);
	stop(EXIT_SUCCESS, std::cout, std::to_string(result));
} catch (const std::exception& exception) {
	stop(EXIT_FAILURE, std::cerr, fmt::format("error: {:s}", exception.what()));
}
