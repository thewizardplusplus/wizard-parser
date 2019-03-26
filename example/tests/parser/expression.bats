load "../common/common"

declare -gra OPTIONS=("--stdin" "--target" "cst")

@test "parser: expression, with a minus and a multiplication" {
	declare -r INPUT="-x * y"
	declare -r OUTPUT='{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"offset":0,"type":"minus","value":"-"},{"children":[{"offset":1,"type":"identifier","value":"x"}],"type":"atom"}],"type":"sequence"}],"type":"unary"},{"offset":3,"type":"star","value":"*"},{"children":[{"children":[{"children":[{"offset":5,"type":"identifier","value":"y"}],"type":"atom"}],"type":"sequence"}],"type":"unary"}],"type":"sequence"}],"type":"product"}],"type":"sequence"}],"type":"sum"}'
	test_json_output
}

@test "parser: expression, with a minus, a multiplication and a grouping" {
	declare -r INPUT="-(x * y)"
	declare -r OUTPUT='{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"offset":0,"type":"minus","value":"-"},{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"offset":2,"type":"identifier","value":"x"}],"type":"atom"}],"type":"sequence"}],"type":"unary"},{"offset":4,"type":"star","value":"*"},{"children":[{"children":[{"children":[{"offset":6,"type":"identifier","value":"y"}],"type":"atom"}],"type":"sequence"}],"type":"unary"}],"type":"sequence"}],"type":"product"}],"type":"sequence"}],"type":"sum"}],"type":"sequence"}],"type":"atom"}],"type":"sequence"}],"type":"unary"}],"type":"sequence"}],"type":"product"}],"type":"sequence"}],"type":"sum"}'
	test_json_output
}

@test "parser: expression, with a multiplication and an addition" {
	declare -r INPUT="x * y + z"
	declare -r OUTPUT='{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"offset":0,"type":"identifier","value":"x"}],"type":"atom"}],"type":"sequence"}],"type":"unary"},{"offset":2,"type":"star","value":"*"},{"children":[{"children":[{"children":[{"offset":4,"type":"identifier","value":"y"}],"type":"atom"}],"type":"sequence"}],"type":"unary"}],"type":"sequence"}],"type":"product"},{"offset":6,"type":"plus","value":"+"},{"children":[{"children":[{"children":[{"children":[{"children":[{"offset":8,"type":"identifier","value":"z"}],"type":"atom"}],"type":"sequence"}],"type":"unary"}],"type":"sequence"}],"type":"product"}],"type":"sequence"}],"type":"sum"}'
	test_json_output
}

@test "parser: expression, with a multiplication, an addition and a grouping" {
	declare -r INPUT="x * (y + z)"
	declare -r OUTPUT='{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"offset":0,"type":"identifier","value":"x"}],"type":"atom"}],"type":"sequence"}],"type":"unary"},{"offset":2,"type":"star","value":"*"},{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"offset":5,"type":"identifier","value":"y"}],"type":"atom"}],"type":"sequence"}],"type":"unary"}],"type":"sequence"}],"type":"product"},{"offset":7,"type":"plus","value":"+"},{"children":[{"children":[{"children":[{"children":[{"children":[{"offset":9,"type":"identifier","value":"z"}],"type":"atom"}],"type":"sequence"}],"type":"unary"}],"type":"sequence"}],"type":"product"}],"type":"sequence"}],"type":"sum"}],"type":"sequence"}],"type":"atom"}],"type":"sequence"}],"type":"unary"}],"type":"sequence"}],"type":"product"}],"type":"sequence"}],"type":"sum"}'
	test_json_output
}
