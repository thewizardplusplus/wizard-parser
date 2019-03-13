load "../common/test_json_output"

declare -gra OPTIONS=("--stdin")

@test "parser: equality, with an one equal sign" {
	declare -r INPUT="x == y"
	declare -r OUTPUT='{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"offset":0,"type":"sequence"},{"children":[{"children":[{"offset":0,"type":"base_identifier","value":"x"}],"type":"identifier"}],"type":"atom"}],"type":"sequence"}],"type":"unary"},{"offset":2,"type":"sequence"}],"type":"sequence"}],"type":"product"},{"offset":2,"type":"sequence"}],"type":"sequence"}],"type":"sum"},{"offset":2,"type":"sequence"}],"type":"sequence"}],"type":"comparison"},{"children":[{"children":[{"offset":2,"type":"equal","value":"=="},{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"offset":5,"type":"sequence"},{"children":[{"children":[{"offset":5,"type":"base_identifier","value":"y"}],"type":"identifier"}],"type":"atom"}],"type":"sequence"}],"type":"unary"},{"offset":6,"type":"sequence"}],"type":"sequence"}],"type":"product"},{"offset":6,"type":"sequence"}],"type":"sequence"}],"type":"sum"},{"offset":6,"type":"sequence"}],"type":"sequence"}],"type":"comparison"}],"type":"sequence"},{"offset":6,"type":"sequence"}],"type":"sequence"}],"type":"sequence"}],"type":"equality"},{"offset":6,"type":"sequence"}],"type":"sequence"}],"type":"conjunction"},{"offset":6,"type":"sequence"}],"type":"sequence"}],"type":"disjunction"}'
	test_json_output
}

@test "parser: equality, with an one not-equal sign" {
	declare -r INPUT="x /= y"
	declare -r OUTPUT='{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"offset":0,"type":"sequence"},{"children":[{"children":[{"offset":0,"type":"base_identifier","value":"x"}],"type":"identifier"}],"type":"atom"}],"type":"sequence"}],"type":"unary"},{"offset":2,"type":"sequence"}],"type":"sequence"}],"type":"product"},{"offset":2,"type":"sequence"}],"type":"sequence"}],"type":"sum"},{"offset":2,"type":"sequence"}],"type":"sequence"}],"type":"comparison"},{"children":[{"children":[{"offset":2,"type":"not_equal","value":"/="},{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"offset":5,"type":"sequence"},{"children":[{"children":[{"offset":5,"type":"base_identifier","value":"y"}],"type":"identifier"}],"type":"atom"}],"type":"sequence"}],"type":"unary"},{"offset":6,"type":"sequence"}],"type":"sequence"}],"type":"product"},{"offset":6,"type":"sequence"}],"type":"sequence"}],"type":"sum"},{"offset":6,"type":"sequence"}],"type":"sequence"}],"type":"comparison"}],"type":"sequence"},{"offset":6,"type":"sequence"}],"type":"sequence"}],"type":"sequence"}],"type":"equality"},{"offset":6,"type":"sequence"}],"type":"sequence"}],"type":"conjunction"},{"offset":6,"type":"sequence"}],"type":"sequence"}],"type":"disjunction"}'
	test_json_output
}

@test "parser: equality, with some (two) equal signs" {
	declare -r INPUT="x == y == z"
	declare -r OUTPUT='{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"offset":0,"type":"sequence"},{"children":[{"children":[{"offset":0,"type":"base_identifier","value":"x"}],"type":"identifier"}],"type":"atom"}],"type":"sequence"}],"type":"unary"},{"offset":2,"type":"sequence"}],"type":"sequence"}],"type":"product"},{"offset":2,"type":"sequence"}],"type":"sequence"}],"type":"sum"},{"offset":2,"type":"sequence"}],"type":"sequence"}],"type":"comparison"},{"children":[{"children":[{"offset":2,"type":"equal","value":"=="},{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"offset":5,"type":"sequence"},{"children":[{"children":[{"offset":5,"type":"base_identifier","value":"y"}],"type":"identifier"}],"type":"atom"}],"type":"sequence"}],"type":"unary"},{"offset":7,"type":"sequence"}],"type":"sequence"}],"type":"product"},{"offset":7,"type":"sequence"}],"type":"sequence"}],"type":"sum"},{"offset":7,"type":"sequence"}],"type":"sequence"}],"type":"comparison"}],"type":"sequence"},{"children":[{"children":[{"offset":7,"type":"equal","value":"=="},{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"offset":10,"type":"sequence"},{"children":[{"children":[{"offset":10,"type":"base_identifier","value":"z"}],"type":"identifier"}],"type":"atom"}],"type":"sequence"}],"type":"unary"},{"offset":11,"type":"sequence"}],"type":"sequence"}],"type":"product"},{"offset":11,"type":"sequence"}],"type":"sequence"}],"type":"sum"},{"offset":11,"type":"sequence"}],"type":"sequence"}],"type":"comparison"}],"type":"sequence"},{"offset":11,"type":"sequence"}],"type":"sequence"}],"type":"sequence"}],"type":"sequence"}],"type":"equality"},{"offset":11,"type":"sequence"}],"type":"sequence"}],"type":"conjunction"},{"offset":11,"type":"sequence"}],"type":"sequence"}],"type":"disjunction"}'
	test_json_output
}

@test "parser: equality, with some (three) equal signs" {
	declare -r INPUT="x == y == z == w"
	declare -r OUTPUT='{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"offset":0,"type":"sequence"},{"children":[{"children":[{"offset":0,"type":"base_identifier","value":"x"}],"type":"identifier"}],"type":"atom"}],"type":"sequence"}],"type":"unary"},{"offset":2,"type":"sequence"}],"type":"sequence"}],"type":"product"},{"offset":2,"type":"sequence"}],"type":"sequence"}],"type":"sum"},{"offset":2,"type":"sequence"}],"type":"sequence"}],"type":"comparison"},{"children":[{"children":[{"offset":2,"type":"equal","value":"=="},{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"offset":5,"type":"sequence"},{"children":[{"children":[{"offset":5,"type":"base_identifier","value":"y"}],"type":"identifier"}],"type":"atom"}],"type":"sequence"}],"type":"unary"},{"offset":7,"type":"sequence"}],"type":"sequence"}],"type":"product"},{"offset":7,"type":"sequence"}],"type":"sequence"}],"type":"sum"},{"offset":7,"type":"sequence"}],"type":"sequence"}],"type":"comparison"}],"type":"sequence"},{"children":[{"children":[{"offset":7,"type":"equal","value":"=="},{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"offset":10,"type":"sequence"},{"children":[{"children":[{"offset":10,"type":"base_identifier","value":"z"}],"type":"identifier"}],"type":"atom"}],"type":"sequence"}],"type":"unary"},{"offset":12,"type":"sequence"}],"type":"sequence"}],"type":"product"},{"offset":12,"type":"sequence"}],"type":"sequence"}],"type":"sum"},{"offset":12,"type":"sequence"}],"type":"sequence"}],"type":"comparison"}],"type":"sequence"},{"children":[{"children":[{"offset":12,"type":"equal","value":"=="},{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"offset":15,"type":"sequence"},{"children":[{"children":[{"offset":15,"type":"base_identifier","value":"w"}],"type":"identifier"}],"type":"atom"}],"type":"sequence"}],"type":"unary"},{"offset":16,"type":"sequence"}],"type":"sequence"}],"type":"product"},{"offset":16,"type":"sequence"}],"type":"sequence"}],"type":"sum"},{"offset":16,"type":"sequence"}],"type":"sequence"}],"type":"comparison"}],"type":"sequence"},{"offset":16,"type":"sequence"}],"type":"sequence"}],"type":"sequence"}],"type":"sequence"}],"type":"sequence"}],"type":"equality"},{"offset":16,"type":"sequence"}],"type":"sequence"}],"type":"conjunction"},{"offset":16,"type":"sequence"}],"type":"sequence"}],"type":"disjunction"}'
	test_json_output
}

@test "parser: equality, with one equal and not-equal signs" {
	declare -r INPUT="x == y /= z"
	declare -r OUTPUT='{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"offset":0,"type":"sequence"},{"children":[{"children":[{"offset":0,"type":"base_identifier","value":"x"}],"type":"identifier"}],"type":"atom"}],"type":"sequence"}],"type":"unary"},{"offset":2,"type":"sequence"}],"type":"sequence"}],"type":"product"},{"offset":2,"type":"sequence"}],"type":"sequence"}],"type":"sum"},{"offset":2,"type":"sequence"}],"type":"sequence"}],"type":"comparison"},{"children":[{"children":[{"offset":2,"type":"equal","value":"=="},{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"offset":5,"type":"sequence"},{"children":[{"children":[{"offset":5,"type":"base_identifier","value":"y"}],"type":"identifier"}],"type":"atom"}],"type":"sequence"}],"type":"unary"},{"offset":7,"type":"sequence"}],"type":"sequence"}],"type":"product"},{"offset":7,"type":"sequence"}],"type":"sequence"}],"type":"sum"},{"offset":7,"type":"sequence"}],"type":"sequence"}],"type":"comparison"}],"type":"sequence"},{"children":[{"children":[{"offset":7,"type":"not_equal","value":"/="},{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"offset":10,"type":"sequence"},{"children":[{"children":[{"offset":10,"type":"base_identifier","value":"z"}],"type":"identifier"}],"type":"atom"}],"type":"sequence"}],"type":"unary"},{"offset":11,"type":"sequence"}],"type":"sequence"}],"type":"product"},{"offset":11,"type":"sequence"}],"type":"sequence"}],"type":"sum"},{"offset":11,"type":"sequence"}],"type":"sequence"}],"type":"comparison"}],"type":"sequence"},{"offset":11,"type":"sequence"}],"type":"sequence"}],"type":"sequence"}],"type":"sequence"}],"type":"equality"},{"offset":11,"type":"sequence"}],"type":"sequence"}],"type":"conjunction"},{"offset":11,"type":"sequence"}],"type":"sequence"}],"type":"disjunction"}'
	test_json_output
}
