load "../common/common"

declare -gra OPTIONS=("--stdin" "--tokens")

@test "lexer: plus" {
	declare -r INPUT="+"
	declare -r OUTPUT='[{"offset":0,"type":"plus","value":"+"}]'
	test_json_output
}

@test "lexer: minus" {
	declare -r INPUT="-"
	declare -r OUTPUT='[{"offset":0,"type":"minus","value":"-"}]'
	test_json_output
}

@test "lexer: star" {
	declare -r INPUT="*"
	declare -r OUTPUT='[{"offset":0,"type":"star","value":"*"}]'
	test_json_output
}

@test "lexer: slash" {
	declare -r INPUT="/"
	declare -r OUTPUT='[{"offset":0,"type":"slash","value":"/"}]'
	test_json_output
}

@test "lexer: percent" {
	declare -r INPUT="%"
	declare -r OUTPUT='[{"offset":0,"type":"percent","value":"%"}]'
	test_json_output
}

@test "lexer: opening_parenthesis" {
	declare -r INPUT="("
	declare -r OUTPUT='[{"offset":0,"type":"opening_parenthesis","value":"("}]'
	test_json_output
}

@test "lexer: closing_parenthesis" {
	declare -r INPUT=")"
	declare -r OUTPUT='[{"offset":0,"type":"closing_parenthesis","value":")"}]'
	test_json_output
}

@test "lexer: comma" {
	declare -r INPUT=","
	declare -r OUTPUT='[{"offset":0,"type":"comma","value":","}]'
	test_json_output
}
