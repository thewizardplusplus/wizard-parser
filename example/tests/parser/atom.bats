load "../common/io_test"

declare -gra OPTIONS=("--stdin")

@test "parser: number_constant" {
	declare -r INPUT="5"
	declare -r OUTPUT='{"type": "number_constant", "value": "5"}'
	io_test
}

@test "parser: identifier" {
	declare -r INPUT="test"
	declare -r OUTPUT='{"type": "identifier", "value": "test"}'
	io_test
}

@test "parser: function_call, without parameters" {
	declare -r INPUT="test()"
	declare -r OUTPUT='{
		"type": "function_call",
		"children": [{"type": "identifier", "value": "test"}]
	}'
	io_test
}

@test "parser: function_call, with an one parameter" {
	declare -r INPUT="test(5)"
	declare -r OUTPUT='{
		"type": "function_call",
		"children": [
			{"type": "identifier", "value": "test"},
			{"type": "number_constant", "value": "5"}
		]
	}'
	io_test
}

@test "parser: function_call, with some (two) parameters" {
	declare -r INPUT="test(5, 12)"
	declare -r OUTPUT='{
		"type": "function_call",
		"children": [
			{"type": "identifier", "value": "test"},
			{"type": "number_constant", "value": "5"},
			{"type": "number_constant", "value": "12"}
		]
	}'
	io_test
}

@test "parser: function_call, with some (three) parameters" {
	declare -r INPUT="test(5, 12, 23)"
	declare -r OUTPUT='{
		"type": "function_call",
		"children": [
			{"type": "identifier", "value": "test"},
			{"type": "number_constant", "value": "5"},
			{"type": "number_constant", "value": "12"},
			{"type": "number_constant", "value": "23"}
		]
	}'
	io_test
}

@test "parser: atom, with a grouping" {
	declare -r INPUT="(5)"
	declare -r OUTPUT='{"type": "number_constant", "value": "5"}'
	io_test
}
