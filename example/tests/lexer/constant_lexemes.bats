load "../common/io_test"

declare -gra OPTIONS=("--stdin" "--tokens")

@test "lexer: equal" {
	declare -r INPUT="=="
	declare -r OUTPUT='[{"type": "equal", "value": "=="}]'
	io_test
}

@test "lexer: not_equal" {
	declare -r INPUT="/="
	declare -r OUTPUT='[{"type": "not_equal", "value": "/="}]'
	io_test
}

@test "lexer: less" {
	declare -r INPUT="<"
	declare -r OUTPUT='[{"type": "less", "value": "<"}]'
	io_test
}

@test "lexer: less_or_equal" {
	declare -r INPUT="<="
	declare -r OUTPUT='[{"type": "less_or_equal", "value": "<="}]'
	io_test
}

@test "lexer: great" {
	declare -r INPUT=">"
	declare -r OUTPUT='[{"type": "great", "value": ">"}]'
	io_test
}

@test "lexer: great_or_equal" {
	declare -r INPUT=">="
	declare -r OUTPUT='[{"type": "great_or_equal", "value": ">="}]'
	io_test
}

@test "lexer: plus" {
	declare -r INPUT="+"
	declare -r OUTPUT='[{"type": "plus", "value": "+"}]'
	io_test
}

@test "lexer: minus" {
	declare -r INPUT="-"
	declare -r OUTPUT='[{"type": "minus", "value": "-"}]'
	io_test
}

@test "lexer: star" {
	declare -r INPUT="*"
	declare -r OUTPUT='[{"type": "star", "value": "*"}]'
	io_test
}

@test "lexer: slash" {
	declare -r INPUT="/"
	declare -r OUTPUT='[{"type": "slash", "value": "/"}]'
	io_test
}

@test "lexer: percent" {
	declare -r INPUT="%"
	declare -r OUTPUT='[{"type": "percent", "value": "%"}]'
	io_test
}

@test "lexer: opening_parenthesis" {
	declare -r INPUT="("
	declare -r OUTPUT='[{"type": "opening_parenthesis", "value": "("}]'
	io_test
}

@test "lexer: closing_parenthesis" {
	declare -r INPUT=")"
	declare -r OUTPUT='[{"type": "closing_parenthesis", "value": ")"}]'
	io_test
}

@test "lexer: comma" {
	declare -r INPUT=","
	declare -r OUTPUT='[{"type": "comma", "value": ","}]'
	io_test
}
