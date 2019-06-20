load "../common/common"

declare -gra OPTIONS=("--stdin")

@test "errors: unexpected symbol" {
	declare -r INPUT="    #"
	declare -r OUTPUT="error: unexpected symbol (offset: 4)"
	test_text_output stderr
}

@test "errors: unexpected token" {
	declare -r INPUT="    +"
	declare -r OUTPUT="error: unexpected token (offset: 4)"
	test_text_output stderr
}

@test "errors: unexpected token within a concatenation" {
	declare -r INPUT="    x ++ y"
	declare -r OUTPUT="error: unexpected token (offset: 6)"
	test_text_output stderr
}

@test "errors: unexpected token selected between an identifier and a function" {
	declare -r INPUT="    test(5,, 12)"
	declare -r OUTPUT="error: unexpected token (offset: 8)"
	test_text_output stderr
}

@test "errors: unexpected eoi" {
	declare -r INPUT="    -"
	declare -r OUTPUT="error: unexpected eoi (offset: 5)"
	test_text_output stderr
}

@test "errors: unexpected constant" {
	declare -r INPUT="    test"
	declare -r OUTPUT="error: unexpected constant (offset: 4)"
	test_text_output stderr
}
