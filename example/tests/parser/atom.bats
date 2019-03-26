load "../common/common"

declare -gra OPTIONS=("--stdin" "--target" "cst")

@test "parser: number" {
	declare -r INPUT="5"
	declare -r OUTPUT='{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"offset":0,"type":"number","value":"5"}],"type":"atom"}],"type":"sequence"}],"type":"unary"}],"type":"sequence"}],"type":"product"}],"type":"sequence"}],"type":"sum"}'
	test_json_output
}

@test "parser: identifier" {
	declare -r INPUT="test"
	declare -r OUTPUT='{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"offset":0,"type":"identifier","value":"test"}],"type":"atom"}],"type":"sequence"}],"type":"unary"}],"type":"sequence"}],"type":"product"}],"type":"sequence"}],"type":"sum"}'
	test_json_output
}

@test "parser: function_call, without parameters" {
	declare -r INPUT="test()"
	declare -r OUTPUT='{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"offset":0,"type":"identifier","value":"test"}],"type":"sequence"}],"type":"function_call"}],"type":"atom"}],"type":"sequence"}],"type":"unary"}],"type":"sequence"}],"type":"product"}],"type":"sequence"}],"type":"sum"}'
	test_json_output
}

@test "parser: function_call, with an one parameter" {
	declare -r INPUT="test(5)"
	declare -r OUTPUT='{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"offset":0,"type":"identifier","value":"test"},{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"offset":5,"type":"number","value":"5"}],"type":"atom"}],"type":"sequence"}],"type":"unary"}],"type":"sequence"}],"type":"product"}],"type":"sequence"}],"type":"sum"}],"type":"sequence"}],"type":"function_call"}],"type":"atom"}],"type":"sequence"}],"type":"unary"}],"type":"sequence"}],"type":"product"}],"type":"sequence"}],"type":"sum"}'
	test_json_output
}

@test "parser: function_call, with some (two) parameters" {
	declare -r INPUT="test(5, 12)"
	declare -r OUTPUT='{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"offset":0,"type":"identifier","value":"test"},{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"offset":5,"type":"number","value":"5"}],"type":"atom"}],"type":"sequence"}],"type":"unary"}],"type":"sequence"}],"type":"product"}],"type":"sequence"}],"type":"sum"},{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"offset":8,"type":"number","value":"12"}],"type":"atom"}],"type":"sequence"}],"type":"unary"}],"type":"sequence"}],"type":"product"}],"type":"sequence"}],"type":"sum"}],"type":"sequence"}],"type":"function_call"}],"type":"atom"}],"type":"sequence"}],"type":"unary"}],"type":"sequence"}],"type":"product"}],"type":"sequence"}],"type":"sum"}'
	test_json_output
}

@test "parser: function_call, with some (three) parameters" {
	declare -r INPUT="test(5, 12, 23)"
	declare -r OUTPUT='{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"offset":0,"type":"identifier","value":"test"},{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"offset":5,"type":"number","value":"5"}],"type":"atom"}],"type":"sequence"}],"type":"unary"}],"type":"sequence"}],"type":"product"}],"type":"sequence"}],"type":"sum"},{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"offset":8,"type":"number","value":"12"}],"type":"atom"}],"type":"sequence"}],"type":"unary"}],"type":"sequence"}],"type":"product"}],"type":"sequence"}],"type":"sum"},{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"offset":12,"type":"number","value":"23"}],"type":"atom"}],"type":"sequence"}],"type":"unary"}],"type":"sequence"}],"type":"product"}],"type":"sequence"}],"type":"sum"}],"type":"sequence"}],"type":"function_call"}],"type":"atom"}],"type":"sequence"}],"type":"unary"}],"type":"sequence"}],"type":"product"}],"type":"sequence"}],"type":"sum"}'
	test_json_output
}

@test "parser: atom, with a grouping" {
	declare -r INPUT="(5)"
	declare -r OUTPUT='{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"offset":1,"type":"number","value":"5"}],"type":"atom"}],"type":"sequence"}],"type":"unary"}],"type":"sequence"}],"type":"product"}],"type":"sequence"}],"type":"sum"}],"type":"sequence"}],"type":"atom"}],"type":"sequence"}],"type":"unary"}],"type":"sequence"}],"type":"product"}],"type":"sequence"}],"type":"sum"}'
	test_json_output
}
