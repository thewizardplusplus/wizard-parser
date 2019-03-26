load "../common/common"

declare -gra OPTIONS=("--stdin" "--target" "tokens")

@test "lexer: number, an integer number with an one digit" {
	declare -r INPUT="5"
	declare -r OUTPUT='[{"offset":0,"type":"number","value":"5"}]'
	test_json_output
}

@test "lexer: number, an integer number with some digits" {
	declare -r INPUT="12"
	declare -r OUTPUT='[{"offset":0,"type":"number","value":"12"}]'
	test_json_output
}

@test "lexer: number, a real number with an one digit in its fractional part" {
	declare -r INPUT="5.5"
	declare -r OUTPUT='[{"offset":0,"type":"number","value":"5.5"}]'
	test_json_output
}

@test "lexer: number, a real number with some digits in its fractional part" {
	declare -r INPUT="5.12"
	declare -r OUTPUT='[{"offset":0,"type":"number","value":"5.12"}]'
	test_json_output
}

@test "lexer: number, an integer number with an exponent with an one digit" {
	declare -r INPUT="5e5"
	declare -r OUTPUT='[{"offset":0,"type":"number","value":"5e5"}]'
	test_json_output
}

@test "lexer: number, an integer number with an exponent with some digits" {
	declare -r INPUT="5e12"
	declare -r OUTPUT='[{"offset":0,"type":"number","value":"5e12"}]'
	test_json_output
}

@test "lexer: number, an integer number with a negative exponent" {
	declare -r INPUT="5e-5"
	declare -r OUTPUT='[{"offset":0,"type":"number","value":"5e-5"}]'
	test_json_output
}

@test "lexer: number, a real number with an exponent" {
	declare -r INPUT="5.5e5"
	declare -r OUTPUT='[{"offset":0,"type":"number","value":"5.5e5"}]'
	test_json_output
}
