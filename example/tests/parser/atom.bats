load "../common/common"

declare -gra OPTIONS=("--stdin")

@test "parser: number" {
	declare -r INPUT="5"
	declare -r OUTPUT='{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"offset":0,"type":"sequence"},{"children":[{"offset":0,"type":"number","value":"5"}],"type":"atom"}],"type":"sequence"}],"type":"unary"},{"offset":1,"type":"sequence"}],"type":"sequence"}],"type":"product"},{"offset":1,"type":"sequence"}],"type":"sequence"}],"type":"sum"}'
	test_json_output
}

@test "parser: identifier" {
	declare -r INPUT="test"
	declare -r OUTPUT='{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"offset":0,"type":"sequence"},{"children":[{"offset":0,"type":"identifier","value":"test"}],"type":"atom"}],"type":"sequence"}],"type":"unary"},{"offset":4,"type":"sequence"}],"type":"sequence"}],"type":"product"},{"offset":4,"type":"sequence"}],"type":"sequence"}],"type":"sum"}'
	test_json_output
}

@test "parser: function_call, without parameters" {
	declare -r INPUT="test()"
	declare -r OUTPUT='{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"offset":0,"type":"sequence"},{"children":[{"children":[{"children":[{"children":[{"children":[{"offset":0,"type":"identifier","value":"test"},{"offset":4,"type":"nothing"}],"type":"sequence"},{"offset":5,"type":"sequence"}],"type":"sequence"},{"offset":5,"type":"nothing"}],"type":"sequence"}],"type":"function_call"}],"type":"atom"}],"type":"sequence"}],"type":"unary"},{"offset":6,"type":"sequence"}],"type":"sequence"}],"type":"product"},{"offset":6,"type":"sequence"}],"type":"sequence"}],"type":"sum"}'
	test_json_output
}

@test "parser: function_call, with an one parameter" {
	declare -r INPUT="test(5)"
	declare -r OUTPUT='{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"offset":0,"type":"sequence"},{"children":[{"children":[{"children":[{"children":[{"children":[{"offset":0,"type":"identifier","value":"test"},{"offset":4,"type":"nothing"}],"type":"sequence"},{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"offset":5,"type":"sequence"},{"children":[{"offset":5,"type":"number","value":"5"}],"type":"atom"}],"type":"sequence"}],"type":"unary"},{"offset":6,"type":"sequence"}],"type":"sequence"}],"type":"product"},{"offset":6,"type":"sequence"}],"type":"sequence"}],"type":"sum"},{"offset":6,"type":"sequence"}],"type":"sequence"},{"offset":6,"type":"sequence"}],"type":"sequence"}],"type":"sequence"},{"offset":6,"type":"nothing"}],"type":"sequence"}],"type":"function_call"}],"type":"atom"}],"type":"sequence"}],"type":"unary"},{"offset":7,"type":"sequence"}],"type":"sequence"}],"type":"product"},{"offset":7,"type":"sequence"}],"type":"sequence"}],"type":"sum"}'
	test_json_output
}

@test "parser: function_call, with some (two) parameters" {
	declare -r INPUT="test(5, 12)"
	declare -r OUTPUT='{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"offset":0,"type":"sequence"},{"children":[{"children":[{"children":[{"children":[{"children":[{"offset":0,"type":"identifier","value":"test"},{"offset":4,"type":"nothing"}],"type":"sequence"},{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"offset":5,"type":"sequence"},{"children":[{"offset":5,"type":"number","value":"5"}],"type":"atom"}],"type":"sequence"}],"type":"unary"},{"offset":6,"type":"sequence"}],"type":"sequence"}],"type":"product"},{"offset":6,"type":"sequence"}],"type":"sequence"}],"type":"sum"},{"children":[{"children":[{"offset":6,"type":"nothing"},{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"offset":8,"type":"sequence"},{"children":[{"offset":8,"type":"number","value":"12"}],"type":"atom"}],"type":"sequence"}],"type":"unary"},{"offset":10,"type":"sequence"}],"type":"sequence"}],"type":"product"},{"offset":10,"type":"sequence"}],"type":"sequence"}],"type":"sum"}],"type":"sequence"},{"offset":10,"type":"sequence"}],"type":"sequence"}],"type":"sequence"},{"offset":10,"type":"sequence"}],"type":"sequence"}],"type":"sequence"},{"offset":10,"type":"nothing"}],"type":"sequence"}],"type":"function_call"}],"type":"atom"}],"type":"sequence"}],"type":"unary"},{"offset":11,"type":"sequence"}],"type":"sequence"}],"type":"product"},{"offset":11,"type":"sequence"}],"type":"sequence"}],"type":"sum"}'
	test_json_output
}

@test "parser: function_call, with some (three) parameters" {
	declare -r INPUT="test(5, 12, 23)"
	declare -r OUTPUT='{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"offset":0,"type":"sequence"},{"children":[{"children":[{"children":[{"children":[{"children":[{"offset":0,"type":"identifier","value":"test"},{"offset":4,"type":"nothing"}],"type":"sequence"},{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"offset":5,"type":"sequence"},{"children":[{"offset":5,"type":"number","value":"5"}],"type":"atom"}],"type":"sequence"}],"type":"unary"},{"offset":6,"type":"sequence"}],"type":"sequence"}],"type":"product"},{"offset":6,"type":"sequence"}],"type":"sequence"}],"type":"sum"},{"children":[{"children":[{"offset":6,"type":"nothing"},{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"offset":8,"type":"sequence"},{"children":[{"offset":8,"type":"number","value":"12"}],"type":"atom"}],"type":"sequence"}],"type":"unary"},{"offset":10,"type":"sequence"}],"type":"sequence"}],"type":"product"},{"offset":10,"type":"sequence"}],"type":"sequence"}],"type":"sum"}],"type":"sequence"},{"children":[{"children":[{"offset":10,"type":"nothing"},{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"offset":12,"type":"sequence"},{"children":[{"offset":12,"type":"number","value":"23"}],"type":"atom"}],"type":"sequence"}],"type":"unary"},{"offset":14,"type":"sequence"}],"type":"sequence"}],"type":"product"},{"offset":14,"type":"sequence"}],"type":"sequence"}],"type":"sum"}],"type":"sequence"},{"offset":14,"type":"sequence"}],"type":"sequence"}],"type":"sequence"}],"type":"sequence"},{"offset":14,"type":"sequence"}],"type":"sequence"}],"type":"sequence"},{"offset":14,"type":"nothing"}],"type":"sequence"}],"type":"function_call"}],"type":"atom"}],"type":"sequence"}],"type":"unary"},{"offset":15,"type":"sequence"}],"type":"sequence"}],"type":"product"},{"offset":15,"type":"sequence"}],"type":"sequence"}],"type":"sum"}'
	test_json_output
}

@test "parser: atom, with a grouping" {
	declare -r INPUT="(5)"
	declare -r OUTPUT='{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"offset":0,"type":"sequence"},{"children":[{"children":[{"children":[{"offset":0,"type":"nothing"},{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"offset":1,"type":"sequence"},{"children":[{"offset":1,"type":"number","value":"5"}],"type":"atom"}],"type":"sequence"}],"type":"unary"},{"offset":2,"type":"sequence"}],"type":"sequence"}],"type":"product"},{"offset":2,"type":"sequence"}],"type":"sequence"}],"type":"sum"}],"type":"sequence"},{"offset":2,"type":"nothing"}],"type":"sequence"}],"type":"atom"}],"type":"sequence"}],"type":"unary"},{"offset":3,"type":"sequence"}],"type":"sequence"}],"type":"product"},{"offset":3,"type":"sequence"}],"type":"sequence"}],"type":"sum"}'
	test_json_output
}
