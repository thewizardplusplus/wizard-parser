load "../common/io_test"

declare -gra OPTIONS=("--stdin" "--tokens")

@test "lexer: base_identifier, an one upper letter" {
	declare -r INPUT="T"
	declare -r OUTPUT='[{"offset":0,"type":"base_identifier","value":"T"}]'
	io_test
}

@test "lexer: base_identifier, an one lower letter" {
	declare -r INPUT="t"
	declare -r OUTPUT='[{"offset":0,"type":"base_identifier","value":"t"}]'
	io_test
}

@test "lexer: base_identifier, an one underscore" {
	declare -r INPUT="_"
	declare -r OUTPUT='[{"offset":0,"type":"base_identifier","value":"_"}]'
	io_test
}

@test "lexer: base_identifier, some upper letters" {
	declare -r INPUT="TEST"
	declare -r OUTPUT='[{"offset":0,"type":"base_identifier","value":"TEST"}]'
	io_test
}

@test "lexer: base_identifier, some lower letters" {
	declare -r INPUT="test"
	declare -r OUTPUT='[{"offset":0,"type":"base_identifier","value":"test"}]'
	io_test
}

@test "lexer: base_identifier, some underscores" {
	declare -r INPUT="_____"
	declare -r OUTPUT='[{"offset":0,"type":"base_identifier","value":"_____"}]'
	io_test
}

@test "lexer: base_identifier, an one underscore and some digits" {
	declare -r INPUT="_12345"
	declare -r OUTPUT='[{"offset":0,"type":"base_identifier","value":"_12345"}]'
	io_test
}

@test "lexer: base_identifier, some upper letters and underscores" {
	declare -r INPUT="SOME_SIMPLE_TEST"
	declare -r OUTPUT='[{"offset":0,"type":"base_identifier","value":"SOME_SIMPLE_TEST"}]'
	io_test
}

@test "lexer: base_identifier, some upper letters, underscores and digits" {
	declare -r INPUT="SOME_SIMPLE_TEST_12"
	declare -r OUTPUT='[{"offset":0,"type":"base_identifier","value":"SOME_SIMPLE_TEST_12"}]'
	io_test
}

@test "lexer: base_identifier, some lower letters and underscores" {
	declare -r INPUT="some_simple_test"
	declare -r OUTPUT='[{"offset":0,"type":"base_identifier","value":"some_simple_test"}]'
	io_test
}

@test "lexer: base_identifier, some lower letters, underscores and digits" {
	declare -r INPUT="some_simple_test_12"
	declare -r OUTPUT='[{"offset":0,"type":"base_identifier","value":"some_simple_test_12"}]'
	io_test
}

@test "lexer: base_identifier, some upper and lower letters" {
	declare -r INPUT="SomeSimpleTest"
	declare -r OUTPUT='[{"offset":0,"type":"base_identifier","value":"SomeSimpleTest"}]'
	io_test
}

@test "lexer: base_identifier, some upper and lower letters and digits" {
	declare -r INPUT="SomeSimpleTest12"
	declare -r OUTPUT='[{"offset":0,"type":"base_identifier","value":"SomeSimpleTest12"}]'
	io_test
}
