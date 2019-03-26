load "../common/common"

declare -gra OPTIONS=("--stdin" "--target" "cst")

@test "parser: sum, with an one addition" {
	declare -r INPUT="x + y"
	declare -r OUTPUT='{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"offset":0,"type":"sequence"},{"children":[{"offset":0,"type":"identifier","value":"x"}],"type":"atom"}],"type":"sequence"}],"type":"unary"},{"offset":2,"type":"sequence"}],"type":"sequence"}],"type":"product"},{"children":[{"children":[{"offset":2,"type":"plus","value":"+"},{"children":[{"children":[{"children":[{"children":[{"offset":4,"type":"sequence"},{"children":[{"offset":4,"type":"identifier","value":"y"}],"type":"atom"}],"type":"sequence"}],"type":"unary"},{"offset":5,"type":"sequence"}],"type":"sequence"}],"type":"product"}],"type":"sequence"},{"offset":5,"type":"sequence"}],"type":"sequence"}],"type":"sequence"}],"type":"sum"}'
	test_json_output
}

@test "parser: sum, with an one subtraction" {
	declare -r INPUT="x - y"
	declare -r OUTPUT='{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"offset":0,"type":"sequence"},{"children":[{"offset":0,"type":"identifier","value":"x"}],"type":"atom"}],"type":"sequence"}],"type":"unary"},{"offset":2,"type":"sequence"}],"type":"sequence"}],"type":"product"},{"children":[{"children":[{"offset":2,"type":"minus","value":"-"},{"children":[{"children":[{"children":[{"children":[{"offset":4,"type":"sequence"},{"children":[{"offset":4,"type":"identifier","value":"y"}],"type":"atom"}],"type":"sequence"}],"type":"unary"},{"offset":5,"type":"sequence"}],"type":"sequence"}],"type":"product"}],"type":"sequence"},{"offset":5,"type":"sequence"}],"type":"sequence"}],"type":"sequence"}],"type":"sum"}'
	test_json_output
}

@test "parser: sum, with some (two) additions" {
	declare -r INPUT="x + y + z"
	declare -r OUTPUT='{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"offset":0,"type":"sequence"},{"children":[{"offset":0,"type":"identifier","value":"x"}],"type":"atom"}],"type":"sequence"}],"type":"unary"},{"offset":2,"type":"sequence"}],"type":"sequence"}],"type":"product"},{"children":[{"children":[{"offset":2,"type":"plus","value":"+"},{"children":[{"children":[{"children":[{"children":[{"offset":4,"type":"sequence"},{"children":[{"offset":4,"type":"identifier","value":"y"}],"type":"atom"}],"type":"sequence"}],"type":"unary"},{"offset":6,"type":"sequence"}],"type":"sequence"}],"type":"product"}],"type":"sequence"},{"children":[{"children":[{"offset":6,"type":"plus","value":"+"},{"children":[{"children":[{"children":[{"children":[{"offset":8,"type":"sequence"},{"children":[{"offset":8,"type":"identifier","value":"z"}],"type":"atom"}],"type":"sequence"}],"type":"unary"},{"offset":9,"type":"sequence"}],"type":"sequence"}],"type":"product"}],"type":"sequence"},{"offset":9,"type":"sequence"}],"type":"sequence"}],"type":"sequence"}],"type":"sequence"}],"type":"sum"}'
	test_json_output
}

@test "parser: sum, with some (three) additions" {
	declare -r INPUT="x + y + z + w"
	declare -r OUTPUT='{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"offset":0,"type":"sequence"},{"children":[{"offset":0,"type":"identifier","value":"x"}],"type":"atom"}],"type":"sequence"}],"type":"unary"},{"offset":2,"type":"sequence"}],"type":"sequence"}],"type":"product"},{"children":[{"children":[{"offset":2,"type":"plus","value":"+"},{"children":[{"children":[{"children":[{"children":[{"offset":4,"type":"sequence"},{"children":[{"offset":4,"type":"identifier","value":"y"}],"type":"atom"}],"type":"sequence"}],"type":"unary"},{"offset":6,"type":"sequence"}],"type":"sequence"}],"type":"product"}],"type":"sequence"},{"children":[{"children":[{"offset":6,"type":"plus","value":"+"},{"children":[{"children":[{"children":[{"children":[{"offset":8,"type":"sequence"},{"children":[{"offset":8,"type":"identifier","value":"z"}],"type":"atom"}],"type":"sequence"}],"type":"unary"},{"offset":10,"type":"sequence"}],"type":"sequence"}],"type":"product"}],"type":"sequence"},{"children":[{"children":[{"offset":10,"type":"plus","value":"+"},{"children":[{"children":[{"children":[{"children":[{"offset":12,"type":"sequence"},{"children":[{"offset":12,"type":"identifier","value":"w"}],"type":"atom"}],"type":"sequence"}],"type":"unary"},{"offset":13,"type":"sequence"}],"type":"sequence"}],"type":"product"}],"type":"sequence"},{"offset":13,"type":"sequence"}],"type":"sequence"}],"type":"sequence"}],"type":"sequence"}],"type":"sequence"}],"type":"sum"}'
	test_json_output
}

@test "parser: sum, with an one addition and a subtraction" {
	declare -r INPUT="x + y - z"
	declare -r OUTPUT='{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"offset":0,"type":"sequence"},{"children":[{"offset":0,"type":"identifier","value":"x"}],"type":"atom"}],"type":"sequence"}],"type":"unary"},{"offset":2,"type":"sequence"}],"type":"sequence"}],"type":"product"},{"children":[{"children":[{"offset":2,"type":"plus","value":"+"},{"children":[{"children":[{"children":[{"children":[{"offset":4,"type":"sequence"},{"children":[{"offset":4,"type":"identifier","value":"y"}],"type":"atom"}],"type":"sequence"}],"type":"unary"},{"offset":6,"type":"sequence"}],"type":"sequence"}],"type":"product"}],"type":"sequence"},{"children":[{"children":[{"offset":6,"type":"minus","value":"-"},{"children":[{"children":[{"children":[{"children":[{"offset":8,"type":"sequence"},{"children":[{"offset":8,"type":"identifier","value":"z"}],"type":"atom"}],"type":"sequence"}],"type":"unary"},{"offset":9,"type":"sequence"}],"type":"sequence"}],"type":"product"}],"type":"sequence"},{"offset":9,"type":"sequence"}],"type":"sequence"}],"type":"sequence"}],"type":"sequence"}],"type":"sum"}'
	test_json_output
}
