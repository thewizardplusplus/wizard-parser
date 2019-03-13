load "../common/test_json_output"

declare -gra OPTIONS=("--stdin")

@test "parser: unary, with an one minus" {
	declare -r INPUT="-test"
	declare -r OUTPUT='{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"offset":0,"type":"minus","value":"-"},{"offset":1,"type":"sequence"}],"type":"sequence"},{"children":[{"children":[{"offset":1,"type":"base_identifier","value":"test"}],"type":"identifier"}],"type":"atom"}],"type":"sequence"}],"type":"unary"},{"offset":5,"type":"sequence"}],"type":"sequence"}],"type":"product"},{"offset":5,"type":"sequence"}],"type":"sequence"}],"type":"sum"},{"offset":5,"type":"sequence"}],"type":"sequence"}],"type":"comparison"},{"offset":5,"type":"sequence"}],"type":"sequence"}],"type":"equality"},{"offset":5,"type":"sequence"}],"type":"sequence"}],"type":"conjunction"},{"offset":5,"type":"sequence"}],"type":"sequence"}],"type":"disjunction"}'
	test_json_output
}

@test "parser: unary, with an one negation" {
	declare -r INPUT="not test"
	declare -r OUTPUT='{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"offset":0,"type":"base_identifier","value":"not"},{"offset":4,"type":"sequence"}],"type":"sequence"},{"children":[{"children":[{"offset":4,"type":"base_identifier","value":"test"}],"type":"identifier"}],"type":"atom"}],"type":"sequence"}],"type":"unary"},{"offset":8,"type":"sequence"}],"type":"sequence"}],"type":"product"},{"offset":8,"type":"sequence"}],"type":"sequence"}],"type":"sum"},{"offset":8,"type":"sequence"}],"type":"sequence"}],"type":"comparison"},{"offset":8,"type":"sequence"}],"type":"sequence"}],"type":"equality"},{"offset":8,"type":"sequence"}],"type":"sequence"}],"type":"conjunction"},{"offset":8,"type":"sequence"}],"type":"sequence"}],"type":"disjunction"}'
	test_json_output
}

@test "parser: unary, with some (two) minuses" {
	declare -r INPUT="--test"
	declare -r OUTPUT='{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"offset":0,"type":"minus","value":"-"},{"children":[{"offset":1,"type":"minus","value":"-"},{"offset":2,"type":"sequence"}],"type":"sequence"}],"type":"sequence"},{"children":[{"children":[{"offset":2,"type":"base_identifier","value":"test"}],"type":"identifier"}],"type":"atom"}],"type":"sequence"}],"type":"unary"},{"offset":6,"type":"sequence"}],"type":"sequence"}],"type":"product"},{"offset":6,"type":"sequence"}],"type":"sequence"}],"type":"sum"},{"offset":6,"type":"sequence"}],"type":"sequence"}],"type":"comparison"},{"offset":6,"type":"sequence"}],"type":"sequence"}],"type":"equality"},{"offset":6,"type":"sequence"}],"type":"sequence"}],"type":"conjunction"},{"offset":6,"type":"sequence"}],"type":"sequence"}],"type":"disjunction"}'
	test_json_output
}

@test "parser: unary, with some (three) minuses" {
	declare -r INPUT="---test"
	declare -r OUTPUT='{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"offset":0,"type":"minus","value":"-"},{"children":[{"offset":1,"type":"minus","value":"-"},{"children":[{"offset":2,"type":"minus","value":"-"},{"offset":3,"type":"sequence"}],"type":"sequence"}],"type":"sequence"}],"type":"sequence"},{"children":[{"children":[{"offset":3,"type":"base_identifier","value":"test"}],"type":"identifier"}],"type":"atom"}],"type":"sequence"}],"type":"unary"},{"offset":7,"type":"sequence"}],"type":"sequence"}],"type":"product"},{"offset":7,"type":"sequence"}],"type":"sequence"}],"type":"sum"},{"offset":7,"type":"sequence"}],"type":"sequence"}],"type":"comparison"},{"offset":7,"type":"sequence"}],"type":"sequence"}],"type":"equality"},{"offset":7,"type":"sequence"}],"type":"sequence"}],"type":"conjunction"},{"offset":7,"type":"sequence"}],"type":"sequence"}],"type":"disjunction"}'
	test_json_output
}

@test "parser: unary, with an one minus and a negation" {
	declare -r INPUT="-not test"
	declare -r OUTPUT='{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"offset":0,"type":"minus","value":"-"},{"children":[{"offset":1,"type":"base_identifier","value":"not"},{"offset":5,"type":"sequence"}],"type":"sequence"}],"type":"sequence"},{"children":[{"children":[{"offset":5,"type":"base_identifier","value":"test"}],"type":"identifier"}],"type":"atom"}],"type":"sequence"}],"type":"unary"},{"offset":9,"type":"sequence"}],"type":"sequence"}],"type":"product"},{"offset":9,"type":"sequence"}],"type":"sequence"}],"type":"sum"},{"offset":9,"type":"sequence"}],"type":"sequence"}],"type":"comparison"},{"offset":9,"type":"sequence"}],"type":"sequence"}],"type":"equality"},{"offset":9,"type":"sequence"}],"type":"sequence"}],"type":"conjunction"},{"offset":9,"type":"sequence"}],"type":"sequence"}],"type":"disjunction"}'
	test_json_output
}
