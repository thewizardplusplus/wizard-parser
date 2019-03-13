load "../common/common"

declare -gra OPTIONS=("--stdin")

@test "errors: unexpected symbol" {
	declare -r INPUT="    #"
	declare -r OUTPUT="error: unexpected symbol (offset: 4)"
	test_error_output
}

@test "errors: unexpected token" {
	declare -r INPUT="    +"
	declare -r OUTPUT="error: unexpected token (offset: 4)"
	test_error_output
}

@test "errors: unexpected eoi" {
	declare -r INPUT="    -"
	declare -r OUTPUT="error: unexpected eoi (offset: 5)"
	test_error_output
}
