load "../common/common"

declare -gra OPTIONS=("--stdin")

@test "parser: expression, with a minus and a multiplication" {
	declare -r INPUT="-x * y"
	declare -r OUTPUT='{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"offset":0,"type":"minus","value":"-"},{"offset":1,"type":"sequence"}],"type":"sequence"},{"children":[{"offset":1,"type":"identifier","value":"x"}],"type":"atom"}],"type":"sequence"}],"type":"unary"},{"children":[{"children":[{"offset":3,"type":"star","value":"*"},{"children":[{"children":[{"offset":5,"type":"sequence"},{"children":[{"offset":5,"type":"identifier","value":"y"}],"type":"atom"}],"type":"sequence"}],"type":"unary"}],"type":"sequence"},{"offset":6,"type":"sequence"}],"type":"sequence"}],"type":"sequence"}],"type":"product"},{"offset":6,"type":"sequence"}],"type":"sequence"}],"type":"sum"}'
	test_json_output
}

@test "parser: expression, with a minus, a multiplication and a grouping" {
	declare -r INPUT="-(x * y)"
	declare -r OUTPUT='{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"offset":0,"type":"minus","value":"-"},{"offset":1,"type":"sequence"}],"type":"sequence"},{"children":[{"children":[{"children":[{"offset":1,"type":"nothing"},{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"offset":2,"type":"sequence"},{"children":[{"offset":2,"type":"identifier","value":"x"}],"type":"atom"}],"type":"sequence"}],"type":"unary"},{"children":[{"children":[{"offset":4,"type":"star","value":"*"},{"children":[{"children":[{"offset":6,"type":"sequence"},{"children":[{"offset":6,"type":"identifier","value":"y"}],"type":"atom"}],"type":"sequence"}],"type":"unary"}],"type":"sequence"},{"offset":7,"type":"sequence"}],"type":"sequence"}],"type":"sequence"}],"type":"product"},{"offset":7,"type":"sequence"}],"type":"sequence"}],"type":"sum"}],"type":"sequence"},{"offset":7,"type":"nothing"}],"type":"sequence"}],"type":"atom"}],"type":"sequence"}],"type":"unary"},{"offset":8,"type":"sequence"}],"type":"sequence"}],"type":"product"},{"offset":8,"type":"sequence"}],"type":"sequence"}],"type":"sum"}'
	test_json_output
}

@test "parser: expression, with a multiplication and an addition" {
	declare -r INPUT="x * y + z"
	declare -r OUTPUT='{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"offset":0,"type":"sequence"},{"children":[{"offset":0,"type":"identifier","value":"x"}],"type":"atom"}],"type":"sequence"}],"type":"unary"},{"children":[{"children":[{"offset":2,"type":"star","value":"*"},{"children":[{"children":[{"offset":4,"type":"sequence"},{"children":[{"offset":4,"type":"identifier","value":"y"}],"type":"atom"}],"type":"sequence"}],"type":"unary"}],"type":"sequence"},{"offset":6,"type":"sequence"}],"type":"sequence"}],"type":"sequence"}],"type":"product"},{"children":[{"children":[{"offset":6,"type":"plus","value":"+"},{"children":[{"children":[{"children":[{"children":[{"offset":8,"type":"sequence"},{"children":[{"offset":8,"type":"identifier","value":"z"}],"type":"atom"}],"type":"sequence"}],"type":"unary"},{"offset":9,"type":"sequence"}],"type":"sequence"}],"type":"product"}],"type":"sequence"},{"offset":9,"type":"sequence"}],"type":"sequence"}],"type":"sequence"}],"type":"sum"}'
	test_json_output
}

@test "parser: expression, with a multiplication, an addition and a grouping" {
	declare -r INPUT="x * (y + z)"
	declare -r OUTPUT='{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"offset":0,"type":"sequence"},{"children":[{"offset":0,"type":"identifier","value":"x"}],"type":"atom"}],"type":"sequence"}],"type":"unary"},{"children":[{"children":[{"offset":2,"type":"star","value":"*"},{"children":[{"children":[{"offset":4,"type":"sequence"},{"children":[{"children":[{"children":[{"offset":4,"type":"nothing"},{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"offset":5,"type":"sequence"},{"children":[{"offset":5,"type":"identifier","value":"y"}],"type":"atom"}],"type":"sequence"}],"type":"unary"},{"offset":7,"type":"sequence"}],"type":"sequence"}],"type":"product"},{"children":[{"children":[{"offset":7,"type":"plus","value":"+"},{"children":[{"children":[{"children":[{"children":[{"offset":9,"type":"sequence"},{"children":[{"offset":9,"type":"identifier","value":"z"}],"type":"atom"}],"type":"sequence"}],"type":"unary"},{"offset":10,"type":"sequence"}],"type":"sequence"}],"type":"product"}],"type":"sequence"},{"offset":10,"type":"sequence"}],"type":"sequence"}],"type":"sequence"}],"type":"sum"}],"type":"sequence"},{"offset":10,"type":"nothing"}],"type":"sequence"}],"type":"atom"}],"type":"sequence"}],"type":"unary"}],"type":"sequence"},{"offset":11,"type":"sequence"}],"type":"sequence"}],"type":"sequence"}],"type":"product"},{"offset":11,"type":"sequence"}],"type":"sequence"}],"type":"sum"}'
	test_json_output
}
