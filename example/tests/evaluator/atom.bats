load "../common/common"

declare -gra OPTIONS=("--stdin")

@test "evaluator: number" {
	declare -r INPUT="5.12"
	declare -r OUTPUT="5.120000"
	test_text_output
}

@test "evaluator: identifier, pi" {
	declare -r INPUT="pi"
	declare -r OUTPUT="3.141593"
	test_text_output
}

@test "evaluator: identifier, e" {
	declare -r INPUT="e"
	declare -r OUTPUT="2.718282"
	test_text_output
}

@test "evaluator: function_call, with an one parameter, floor()" {
	declare -r INPUT="floor(5.12)"
	declare -r OUTPUT="5.000000"
	test_text_output
}

@test "evaluator: function_call, with an one parameter, ceil()" {
	declare -r INPUT="ceil(5.12)"
	declare -r OUTPUT="6.000000"
	test_text_output
}

@test "evaluator: function_call, with an one parameter, trunc()" {
	declare -r INPUT="trunc(5.12)"
	declare -r OUTPUT="5.000000"
	test_text_output
}

@test "evaluator: function_call, with an one parameter, round()" {
	declare -r INPUT="round(5.12)"
	declare -r OUTPUT="5.000000"
	test_text_output
}

@test "evaluator: function_call, with an one parameter, sin()" {
	declare -r INPUT="sin(5.12)"
	declare -r OUTPUT="-0.918070"
	test_text_output
}

@test "evaluator: function_call, with an one parameter, cos()" {
	declare -r INPUT="cos(5.12)"
	declare -r OUTPUT="0.396417"
	test_text_output
}

@test "evaluator: function_call, with an one parameter, tn()" {
	declare -r INPUT="tn(5.12)"
	declare -r OUTPUT="-2.315920"
	test_text_output
}

@test "evaluator: function_call, with an one parameter, arcsin()" {
	declare -r INPUT="arcsin(0.512)"
	declare -r OUTPUT="0.537512"
	test_text_output
}

@test "evaluator: function_call, with an one parameter, arccos()" {
	declare -r INPUT="arccos(0.512)"
	declare -r OUTPUT="1.033285"
	test_text_output
}

@test "evaluator: function_call, with an one parameter, arctn()" {
	declare -r INPUT="arctn(0.512)"
	declare -r OUTPUT="0.473201"
	test_text_output
}

@test "evaluator: function_call, with an one parameter, sqrt()" {
	declare -r INPUT="sqrt(5.12)"
	declare -r OUTPUT="2.262742"
	test_text_output
}

@test "evaluator: function_call, with an one parameter, exp()" {
	declare -r INPUT="exp(5.12)"
	declare -r OUTPUT="167.335370"
	test_text_output
}

@test "evaluator: function_call, with an one parameter, ln()" {
	declare -r INPUT="ln(5.12)"
	declare -r OUTPUT="1.633154"
	test_text_output
}

@test "evaluator: function_call, with an one parameter, lg()" {
	declare -r INPUT="lg(5.12)"
	declare -r OUTPUT="0.709270"
	test_text_output
}

@test "evaluator: function_call, with an one parameter, abs()" {
	declare -r INPUT="abs(5.12)"
	declare -r OUTPUT="5.120000"
	test_text_output
}

@test "evaluator: function_call, with some (two) parameters, angle()" {
	declare -r INPUT="angle(5, 12)"
	declare -r OUTPUT="1.176005"
	test_text_output
}

@test "evaluator: function_call, with some (two) parameters, pow()" {
	declare -r INPUT="pow(5, 12)"
	declare -r OUTPUT="244140625.000000"
	test_text_output
}

@test "evaluator: atom, with a grouping" {
	declare -r INPUT="(5.12)"
	declare -r OUTPUT="5.120000"
	test_text_output
}
