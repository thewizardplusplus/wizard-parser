load "../common/io_test"

declare -gra OPTIONS=("--stdin" "--tokens")

@test "lexer: whitespace, an one space" {
	declare -r INPUT="5 12"
	declare -r OUTPUT='[
		{"type": "number_constant", "value": "5"},
		{"type": "number_constant", "value": "12"}
	]'
	io_test
}

@test "lexer: whitespace, some spaces" {
	declare -r INPUT="5  12"
	declare -r OUTPUT='[
		{"type": "number_constant", "value": "5"},
		{"type": "number_constant", "value": "12"}
	]'
	io_test
}

@test "lexer: whitespace, a leading space" {
	declare -r INPUT=" 5"
	declare -r OUTPUT='[{"type": "number_constant", "value": "5"}]'
	io_test
}

@test "lexer: whitespace, a finalizing space" {
	declare -r INPUT="5 "
	declare -r OUTPUT='[{"type": "number_constant", "value": "5"}]'
	io_test
}

@test "lexer: whitespace, an one tabulation" {
	declare -r INPUT=$'5\t12'
	declare -r OUTPUT='[
		{"type": "number_constant", "value": "5"},
		{"type": "number_constant", "value": "12"}
	]'
	io_test
}

@test "lexer: whitespace, some tabulations" {
	declare -r INPUT=$'5\t\t12'
	declare -r OUTPUT='[
		{"type": "number_constant", "value": "5"},
		{"type": "number_constant", "value": "12"}
	]'
	io_test
}

@test "lexer: whitespace, a leading tabulation" {
	declare -r INPUT=$'\t5'
	declare -r OUTPUT='[{"type": "number_constant", "value": "5"}]'
	io_test
}

@test "lexer: whitespace, a finalizing tabulation" {
	declare -r INPUT=$'5\t'
	declare -r OUTPUT='[{"type": "number_constant", "value": "5"}]'
	io_test
}

@test "lexer: whitespace, an one line break" {
	declare -r INPUT=$'5\n12'
	declare -r OUTPUT='[
		{"type": "number_constant", "value": "5"},
		{"type": "number_constant", "value": "12"}
	]'
	io_test
}

@test "lexer: whitespace, some line breaks" {
	declare -r INPUT=$'5\n\n12'
	declare -r OUTPUT='[
		{"type": "number_constant", "value": "5"},
		{"type": "number_constant", "value": "12"}
	]'
	io_test
}

@test "lexer: whitespace, a leading line break" {
	declare -r INPUT=$'\n5'
	declare -r OUTPUT='[{"type": "number_constant", "value": "5"}]'
	io_test
}

@test "lexer: whitespace, a finalizing line break" {
	declare -r INPUT=$'5\n'
	declare -r OUTPUT='[{"type": "number_constant", "value": "5"}]'
	io_test
}
