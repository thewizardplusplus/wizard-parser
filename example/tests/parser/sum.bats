load "../common/common"

declare -gra OPTIONS=("--stdin" "--target" "cst")

@test "parser: sum, with an one addition" {
	declare -r INPUT="x + y"
	declare -r OUTPUT='{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"offset":0,"type":"identifier","value":"x"}],"type":"atom"}],"type":"sequence"}],"type":"unary"}],"type":"sequence"}],"type":"product"},{"offset":2,"type":"plus","value":"+"},{"children":[{"children":[{"children":[{"children":[{"children":[{"offset":4,"type":"identifier","value":"y"}],"type":"atom"}],"type":"sequence"}],"type":"unary"}],"type":"sequence"}],"type":"product"}],"type":"sequence"}],"type":"sum"}'
	test_json_output
}

@test "parser: sum, with an one subtraction" {
	declare -r INPUT="x - y"
	declare -r OUTPUT='{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"offset":0,"type":"identifier","value":"x"}],"type":"atom"}],"type":"sequence"}],"type":"unary"}],"type":"sequence"}],"type":"product"},{"offset":2,"type":"minus","value":"-"},{"children":[{"children":[{"children":[{"children":[{"children":[{"offset":4,"type":"identifier","value":"y"}],"type":"atom"}],"type":"sequence"}],"type":"unary"}],"type":"sequence"}],"type":"product"}],"type":"sequence"}],"type":"sum"}'
	test_json_output
}

@test "parser: sum, with some (two) additions" {
	declare -r INPUT="x + y + z"
	declare -r OUTPUT='{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"offset":0,"type":"identifier","value":"x"}],"type":"atom"}],"type":"sequence"}],"type":"unary"}],"type":"sequence"}],"type":"product"},{"offset":2,"type":"plus","value":"+"},{"children":[{"children":[{"children":[{"children":[{"children":[{"offset":4,"type":"identifier","value":"y"}],"type":"atom"}],"type":"sequence"}],"type":"unary"}],"type":"sequence"}],"type":"product"},{"offset":6,"type":"plus","value":"+"},{"children":[{"children":[{"children":[{"children":[{"children":[{"offset":8,"type":"identifier","value":"z"}],"type":"atom"}],"type":"sequence"}],"type":"unary"}],"type":"sequence"}],"type":"product"}],"type":"sequence"}],"type":"sum"}'
	test_json_output
}

@test "parser: sum, with some (three) additions" {
	declare -r INPUT="x + y + z + w"
	declare -r OUTPUT='{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"offset":0,"type":"identifier","value":"x"}],"type":"atom"}],"type":"sequence"}],"type":"unary"}],"type":"sequence"}],"type":"product"},{"offset":2,"type":"plus","value":"+"},{"children":[{"children":[{"children":[{"children":[{"children":[{"offset":4,"type":"identifier","value":"y"}],"type":"atom"}],"type":"sequence"}],"type":"unary"}],"type":"sequence"}],"type":"product"},{"offset":6,"type":"plus","value":"+"},{"children":[{"children":[{"children":[{"children":[{"children":[{"offset":8,"type":"identifier","value":"z"}],"type":"atom"}],"type":"sequence"}],"type":"unary"}],"type":"sequence"}],"type":"product"},{"offset":10,"type":"plus","value":"+"},{"children":[{"children":[{"children":[{"children":[{"children":[{"offset":12,"type":"identifier","value":"w"}],"type":"atom"}],"type":"sequence"}],"type":"unary"}],"type":"sequence"}],"type":"product"}],"type":"sequence"}],"type":"sum"}'
	test_json_output
}

@test "parser: sum, with an one addition and a subtraction" {
	declare -r INPUT="x + y - z"
	declare -r OUTPUT='{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"offset":0,"type":"identifier","value":"x"}],"type":"atom"}],"type":"sequence"}],"type":"unary"}],"type":"sequence"}],"type":"product"},{"offset":2,"type":"plus","value":"+"},{"children":[{"children":[{"children":[{"children":[{"children":[{"offset":4,"type":"identifier","value":"y"}],"type":"atom"}],"type":"sequence"}],"type":"unary"}],"type":"sequence"}],"type":"product"},{"offset":6,"type":"minus","value":"-"},{"children":[{"children":[{"children":[{"children":[{"children":[{"offset":8,"type":"identifier","value":"z"}],"type":"atom"}],"type":"sequence"}],"type":"unary"}],"type":"sequence"}],"type":"product"}],"type":"sequence"}],"type":"sum"}'
	test_json_output
}
