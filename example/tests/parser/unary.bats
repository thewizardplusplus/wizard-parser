load "../common/common"

declare -gra OPTIONS=("--stdin" "--target" "cst")

@test "parser: unary, with an one minus" {
	declare -r INPUT="-test"
	declare -r OUTPUT='{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"offset":0,"type":"minus","value":"-"},{"offset":1,"type":"sequence"}],"type":"sequence"},{"children":[{"offset":1,"type":"identifier","value":"test"}],"type":"atom"}],"type":"sequence"}],"type":"unary"},{"offset":5,"type":"sequence"}],"type":"sequence"}],"type":"product"},{"offset":5,"type":"sequence"}],"type":"sequence"}],"type":"sum"}'
	test_json_output
}

@test "parser: unary, with some (two) minuses" {
	declare -r INPUT="--test"
	declare -r OUTPUT='{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"offset":0,"type":"minus","value":"-"},{"children":[{"offset":1,"type":"minus","value":"-"},{"offset":2,"type":"sequence"}],"type":"sequence"}],"type":"sequence"},{"children":[{"offset":2,"type":"identifier","value":"test"}],"type":"atom"}],"type":"sequence"}],"type":"unary"},{"offset":6,"type":"sequence"}],"type":"sequence"}],"type":"product"},{"offset":6,"type":"sequence"}],"type":"sequence"}],"type":"sum"}'
	test_json_output
}

@test "parser: unary, with some (three) minuses" {
	declare -r INPUT="---test"
	declare -r OUTPUT='{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"offset":0,"type":"minus","value":"-"},{"children":[{"offset":1,"type":"minus","value":"-"},{"children":[{"offset":2,"type":"minus","value":"-"},{"offset":3,"type":"sequence"}],"type":"sequence"}],"type":"sequence"}],"type":"sequence"},{"children":[{"offset":3,"type":"identifier","value":"test"}],"type":"atom"}],"type":"sequence"}],"type":"unary"},{"offset":7,"type":"sequence"}],"type":"sequence"}],"type":"product"},{"offset":7,"type":"sequence"}],"type":"sequence"}],"type":"sum"}'
	test_json_output
}
