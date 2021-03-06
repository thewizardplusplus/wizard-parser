load "../common/common"

declare -gra OPTIONS=("--stdin" "--target" "tokens")

@test "lexer: identifier, an one upper letter" {
	declare -r INPUT="T"
	declare -r OUTPUT='[{"offset":0,"type":"identifier","value":"T"}]'
	test_json_output
}

@test "lexer: identifier, an one lower letter" {
	declare -r INPUT="t"
	declare -r OUTPUT='[{"offset":0,"type":"identifier","value":"t"}]'
	test_json_output
}

@test "lexer: identifier, an one underscore" {
	declare -r INPUT="_"
	declare -r OUTPUT='[{"offset":0,"type":"identifier","value":"_"}]'
	test_json_output
}

@test "lexer: identifier, some upper letters" {
	declare -r INPUT="TEST"
	declare -r OUTPUT='[{"offset":0,"type":"identifier","value":"TEST"}]'
	test_json_output
}

@test "lexer: identifier, some lower letters" {
	declare -r INPUT="test"
	declare -r OUTPUT='[{"offset":0,"type":"identifier","value":"test"}]'
	test_json_output
}

@test "lexer: identifier, some underscores" {
	declare -r INPUT="_____"
	declare -r OUTPUT='[{"offset":0,"type":"identifier","value":"_____"}]'
	test_json_output
}

@test "lexer: identifier, an one underscore and some digits" {
	declare -r INPUT="_12345"
	declare -r OUTPUT='[{"offset":0,"type":"identifier","value":"_12345"}]'
	test_json_output
}

@test "lexer: identifier, some upper letters and underscores" {
	declare -r INPUT="SOME_SIMPLE_TEST"
	declare -r OUTPUT='[{"offset":0,"type":"identifier","value":"SOME_SIMPLE_TEST"}]'
	test_json_output
}

@test "lexer: identifier, some upper letters, underscores and digits" {
	declare -r INPUT="SOME_SIMPLE_TEST_12"
	declare -r OUTPUT='[{"offset":0,"type":"identifier","value":"SOME_SIMPLE_TEST_12"}]'
	test_json_output
}

@test "lexer: identifier, some lower letters and underscores" {
	declare -r INPUT="some_simple_test"
	declare -r OUTPUT='[{"offset":0,"type":"identifier","value":"some_simple_test"}]'
	test_json_output
}

@test "lexer: identifier, some lower letters, underscores and digits" {
	declare -r INPUT="some_simple_test_12"
	declare -r OUTPUT='[{"offset":0,"type":"identifier","value":"some_simple_test_12"}]'
	test_json_output
}

@test "lexer: identifier, some upper and lower letters" {
	declare -r INPUT="SomeSimpleTest"
	declare -r OUTPUT='[{"offset":0,"type":"identifier","value":"SomeSimpleTest"}]'
	test_json_output
}

@test "lexer: identifier, some upper and lower letters and digits" {
	declare -r INPUT="SomeSimpleTest12"
	declare -r OUTPUT='[{"offset":0,"type":"identifier","value":"SomeSimpleTest12"}]'
	test_json_output
}
