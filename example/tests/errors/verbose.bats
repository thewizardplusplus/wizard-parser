load "../common/common"

declare -gra OPTIONS=("--stdin" "--verbose")

@test "errors: verbose, unexpected symbol" {
	declare -r INPUT="    #"
	declare OUTPUT="error: unexpected symbol (offset: 4)"$'\n'
	OUTPUT+='| "    #"'$'\n'
	OUTPUT+='|      ^'

	test_text_output stderr
}

@test "errors: verbose, unexpected token" {
	declare -r INPUT="    +"
	declare OUTPUT="error: unexpected token (offset: 4)"$'\n'
	OUTPUT+='| "    +"'$'\n'
	OUTPUT+='|      ^'

	test_text_output stderr
}

@test "errors: verbose, unexpected eoi" {
	declare -r INPUT="    -"
	declare OUTPUT="error: unexpected eoi (offset: 5)"$'\n'
	OUTPUT+='| "    -"'$'\n'
	OUTPUT+='|       ^'

	test_text_output stderr
}

@test "errors: verbose, unexpected constant" {
	declare -r INPUT="    test"
	declare OUTPUT="error: unexpected constant (offset: 4)"$'\n'
	OUTPUT+='| "    test"'$'\n'
	OUTPUT+='|      ^^^^'

	test_text_output stderr
}

@test "errors: verbose, unexpected function" {
	declare -r INPUT="    test(5, 12)"
	declare OUTPUT="error: unexpected function (offset: 4)"$'\n'
	OUTPUT+='| "    test(5, 12)"'$'\n'
	OUTPUT+='|      ^^^^'

	test_text_output stderr
}
