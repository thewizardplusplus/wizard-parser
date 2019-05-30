load "../common/common"

declare -gra OPTIONS=("--stdin" "--precision" "6")

@test "evaluator: number" {
	declare -r INPUT="5.12"
	declare -r OUTPUT="5.12"
	test_text_output
}

@test "evaluator: identifier, pi" {
	declare -r INPUT="pi"
	declare -r OUTPUT="3.14159"
	test_text_output
}

@test "evaluator: identifier, e" {
	declare -r INPUT="e"
	declare -r OUTPUT="2.71828"
	test_text_output
}

@test "evaluator: function_call, with an one parameter, floor()" {
	declare -r INPUT="floor(5.12)"
	declare -r OUTPUT="5"
	test_text_output
}

@test "evaluator: function_call, with an one parameter, ceil()" {
	declare -r INPUT="ceil(5.12)"
	declare -r OUTPUT="6"
	test_text_output
}

@test "evaluator: function_call, with an one parameter, trunc()" {
	declare -r INPUT="trunc(5.12)"
	declare -r OUTPUT="5"
	test_text_output
}

@test "evaluator: function_call, with an one parameter, round()" {
	declare -r INPUT="round(5.12)"
	declare -r OUTPUT="5"
	test_text_output
}

@test "evaluator: function_call, with an one parameter, sin()" {
	declare -r INPUT="sin(5.12)"
	declare -r OUTPUT="-0.91807"
	test_text_output
}

@test "evaluator: function_call, with an one parameter, cos()" {
	declare -r INPUT="cos(5.12)"
	declare -r OUTPUT="0.396417"
	test_text_output
}

@test "evaluator: function_call, with an one parameter, tn()" {
	declare -r INPUT="tn(5.12)"
	declare -r OUTPUT="-2.31592"
	test_text_output
}

@test "evaluator: function_call, with an one parameter, arcsin()" {
	declare -r INPUT="arcsin(0.512)"
	declare -r OUTPUT="0.537512"
	test_text_output
}

@test "evaluator: function_call, with an one parameter, arccos()" {
	declare -r INPUT="arccos(0.512)"
	declare -r OUTPUT="1.03328"
	test_text_output
}

@test "evaluator: function_call, with an one parameter, arctn()" {
	declare -r INPUT="arctn(0.512)"
	declare -r OUTPUT="0.473201"
	test_text_output
}

@test "evaluator: function_call, with an one parameter, sqrt()" {
	declare -r INPUT="sqrt(5.12)"
	declare -r OUTPUT="2.26274"
	test_text_output
}

@test "evaluator: function_call, with an one parameter, exp()" {
	declare -r INPUT="exp(5.12)"
	declare -r OUTPUT="167.335"
	test_text_output
}

@test "evaluator: function_call, with an one parameter, ln()" {
	declare -r INPUT="ln(5.12)"
	declare -r OUTPUT="1.63315"
	test_text_output
}

@test "evaluator: function_call, with an one parameter, lg()" {
	declare -r INPUT="lg(5.12)"
	declare -r OUTPUT="0.70927"
	test_text_output
}

@test "evaluator: function_call, with an one parameter, abs()" {
	declare -r INPUT="abs(5.12)"
	declare -r OUTPUT="5.12"
	test_text_output
}

@test "evaluator: function_call, with some (two) parameters, angle()" {
	declare -r INPUT="angle(5, 12)"
	declare -r OUTPUT="1.17601"
	test_text_output
}

@test "evaluator: function_call, with some (two) parameters, pow()" {
	declare -r INPUT="pow(5, 12)"
	declare -r OUTPUT="2.44141e+08"
	test_text_output
}

@test "evaluator: atom, with a grouping" {
	declare -r INPUT="(5.12)"
	declare -r OUTPUT="5.12"
	test_text_output
}
