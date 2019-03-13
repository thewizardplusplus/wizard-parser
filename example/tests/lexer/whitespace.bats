load "../common/test_json_output"

declare -gra OPTIONS=("--stdin" "--tokens")

@test "lexer: whitespace, an one space" {
	declare -r INPUT="5 12"
	declare -r OUTPUT='[{"offset":0,"type":"number","value":"5"},{"offset":2,"type":"number","value":"12"}]'
	test_json_output
}

@test "lexer: whitespace, some spaces" {
	declare -r INPUT="5  12"
	declare -r OUTPUT='[{"offset":0,"type":"number","value":"5"},{"offset":3,"type":"number","value":"12"}]'
	test_json_output
}

@test "lexer: whitespace, a leading space" {
	declare -r INPUT=" 5"
	declare -r OUTPUT='[{"offset":1,"type":"number","value":"5"}]'
	test_json_output
}

@test "lexer: whitespace, a finalizing space" {
	declare -r INPUT="5 "
	declare -r OUTPUT='[{"offset":0,"type":"number","value":"5"}]'
	test_json_output
}

@test "lexer: whitespace, an one tabulation" {
	declare -r INPUT=$'5\t12'
	declare -r OUTPUT='[{"offset":0,"type":"number","value":"5"},{"offset":2,"type":"number","value":"12"}]'
	test_json_output
}

@test "lexer: whitespace, some tabulations" {
	declare -r INPUT=$'5\t\t12'
	declare -r OUTPUT='[{"offset":0,"type":"number","value":"5"},{"offset":3,"type":"number","value":"12"}]'
	test_json_output
}

@test "lexer: whitespace, a leading tabulation" {
	declare -r INPUT=$'\t5'
	declare -r OUTPUT='[{"offset":1,"type":"number","value":"5"}]'
	test_json_output
}

@test "lexer: whitespace, a finalizing tabulation" {
	declare -r INPUT=$'5\t'
	declare -r OUTPUT='[{"offset":0,"type":"number","value":"5"}]'
	test_json_output
}

@test "lexer: whitespace, an one line break" {
	declare -r INPUT=$'5\n12'
	declare -r OUTPUT='[{"offset":0,"type":"number","value":"5"},{"offset":2,"type":"number","value":"12"}]'
	test_json_output
}

@test "lexer: whitespace, some line breaks" {
	declare -r INPUT=$'5\n\n12'
	declare -r OUTPUT='[{"offset":0,"type":"number","value":"5"},{"offset":3,"type":"number","value":"12"}]'
	test_json_output
}

@test "lexer: whitespace, a leading line break" {
	declare -r INPUT=$'\n5'
	declare -r OUTPUT='[{"offset":1,"type":"number","value":"5"}]'
	test_json_output
}

@test "lexer: whitespace, a finalizing line break" {
	declare -r INPUT=$'5\n'
	declare -r OUTPUT='[{"offset":0,"type":"number","value":"5"}]'
	test_json_output
}
