load "../common/io_test"

declare -gra OPTIONS=("--stdin" "--tokens")

@test "lexer: equal" {
	declare -r INPUT="=="
	declare -r OUTPUT='[{"offset":0,"type":"equal","value":"=="}]'
	io_test
}

@test "lexer: not_equal" {
	declare -r INPUT="/="
	declare -r OUTPUT='[{"offset":0,"type":"not_equal","value":"/="}]'
	io_test
}

@test "lexer: less" {
	declare -r INPUT="<"
	declare -r OUTPUT='[{"offset":0,"type":"less","value":"<"}]'
	io_test
}

@test "lexer: less_or_equal" {
	declare -r INPUT="<="
	declare -r OUTPUT='[{"offset":0,"type":"less_or_equal","value":"<="}]'
	io_test
}

@test "lexer: great" {
	declare -r INPUT=">"
	declare -r OUTPUT='[{"offset":0,"type":"great","value":">"}]'
	io_test
}

@test "lexer: great_or_equal" {
	declare -r INPUT=">="
	declare -r OUTPUT='[{"offset":0,"type":"great_or_equal","value":">="}]'
	io_test
}

@test "lexer: plus" {
	declare -r INPUT="+"
	declare -r OUTPUT='[{"offset":0,"type":"plus","value":"+"}]'
	io_test
}

@test "lexer: minus" {
	declare -r INPUT="-"
	declare -r OUTPUT='[{"offset":0,"type":"minus","value":"-"}]'
	io_test
}

@test "lexer: star" {
	declare -r INPUT="*"
	declare -r OUTPUT='[{"offset":0,"type":"star","value":"*"}]'
	io_test
}

@test "lexer: slash" {
	declare -r INPUT="/"
	declare -r OUTPUT='[{"offset":0,"type":"slash","value":"/"}]'
	io_test
}

@test "lexer: percent" {
	declare -r INPUT="%"
	declare -r OUTPUT='[{"offset":0,"type":"percent","value":"%"}]'
	io_test
}

@test "lexer: opening_parenthesis" {
	declare -r INPUT="("
	declare -r OUTPUT='[{"offset":0,"type":"opening_parenthesis","value":"("}]'
	io_test
}

@test "lexer: closing_parenthesis" {
	declare -r INPUT=")"
	declare -r OUTPUT='[{"offset":0,"type":"closing_parenthesis","value":")"}]'
	io_test
}

@test "lexer: comma" {
	declare -r INPUT=","
	declare -r OUTPUT='[{"offset":0,"type":"comma","value":","}]'
	io_test
}
