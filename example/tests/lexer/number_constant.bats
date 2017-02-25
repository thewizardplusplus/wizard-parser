load "../common/io_test"

declare -gra OPTIONS=("--stdin" "--tokens")

@test "lexer: number_constant, an integer number with an one digit" {
	declare -r INPUT="5"
	declare -r OUTPUT='[{"type": "number_constant", "value": "5"}]'
	io_test
}

@test "lexer: number_constant, an integer number with some digits" {
	declare -r INPUT="12"
	declare -r OUTPUT='[{"type": "number_constant", "value": "12"}]'
	io_test
}

@test "lexer: number_constant, a real number with an one digit in its fractional part" {
	declare -r INPUT="5.5"
	declare -r OUTPUT='[{"type": "number_constant", "value": "5.5"}]'
	io_test
}

@test "lexer: number_constant, a real number with some digits in its fractional part" {
	declare -r INPUT="5.12"
	declare -r OUTPUT='[{"type": "number_constant", "value": "5.12"}]'
	io_test
}

@test "lexer: number_constant, an integer number with an exponent with an one digit" {
	declare -r INPUT="5e5"
	declare -r OUTPUT='[{"type": "number_constant", "value": "5e5"}]'
	io_test
}

@test "lexer: number_constant, an integer number with an exponent with some digits" {
	declare -r INPUT="5e12"
	declare -r OUTPUT='[{"type": "number_constant", "value": "5e12"}]'
	io_test
}

@test "lexer: number_constant, an integer number with a negative exponent" {
	declare -r INPUT="5e-5"
	declare -r OUTPUT='[{"type": "number_constant", "value": "5e-5"}]'
	io_test
}

@test "lexer: number_constant, a real number with an exponent" {
	declare -r INPUT="5.5e5"
	declare -r OUTPUT='[{"type": "number_constant", "value": "5.5e5"}]'
	io_test
}
