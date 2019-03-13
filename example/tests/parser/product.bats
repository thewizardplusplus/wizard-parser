load "../common/test_json_output"

declare -gra OPTIONS=("--stdin")

@test "parser: product, with an one multiplication" {
	declare -r INPUT="x * y"
	declare -r OUTPUT='{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"offset":0,"type":"sequence"},{"children":[{"children":[{"offset":0,"type":"base_identifier","value":"x"}],"type":"identifier"}],"type":"atom"}],"type":"sequence"}],"type":"unary"},{"children":[{"children":[{"offset":2,"type":"star","value":"*"},{"children":[{"children":[{"offset":4,"type":"sequence"},{"children":[{"children":[{"offset":4,"type":"base_identifier","value":"y"}],"type":"identifier"}],"type":"atom"}],"type":"sequence"}],"type":"unary"}],"type":"sequence"},{"offset":5,"type":"sequence"}],"type":"sequence"}],"type":"sequence"}],"type":"product"},{"offset":5,"type":"sequence"}],"type":"sequence"}],"type":"sum"},{"offset":5,"type":"sequence"}],"type":"sequence"}],"type":"comparison"},{"offset":5,"type":"sequence"}],"type":"sequence"}],"type":"equality"},{"offset":5,"type":"sequence"}],"type":"sequence"}],"type":"conjunction"},{"offset":5,"type":"sequence"}],"type":"sequence"}],"type":"disjunction"}'
	test_json_output
}

@test "parser: product, with an one division" {
	declare -r INPUT="x / y"
	declare -r OUTPUT='{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"offset":0,"type":"sequence"},{"children":[{"children":[{"offset":0,"type":"base_identifier","value":"x"}],"type":"identifier"}],"type":"atom"}],"type":"sequence"}],"type":"unary"},{"children":[{"children":[{"offset":2,"type":"slash","value":"/"},{"children":[{"children":[{"offset":4,"type":"sequence"},{"children":[{"children":[{"offset":4,"type":"base_identifier","value":"y"}],"type":"identifier"}],"type":"atom"}],"type":"sequence"}],"type":"unary"}],"type":"sequence"},{"offset":5,"type":"sequence"}],"type":"sequence"}],"type":"sequence"}],"type":"product"},{"offset":5,"type":"sequence"}],"type":"sequence"}],"type":"sum"},{"offset":5,"type":"sequence"}],"type":"sequence"}],"type":"comparison"},{"offset":5,"type":"sequence"}],"type":"sequence"}],"type":"equality"},{"offset":5,"type":"sequence"}],"type":"sequence"}],"type":"conjunction"},{"offset":5,"type":"sequence"}],"type":"sequence"}],"type":"disjunction"}'
	test_json_output
}

@test "parser: product, with an one modulo" {
	declare -r INPUT="x % y"
	declare -r OUTPUT='{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"offset":0,"type":"sequence"},{"children":[{"children":[{"offset":0,"type":"base_identifier","value":"x"}],"type":"identifier"}],"type":"atom"}],"type":"sequence"}],"type":"unary"},{"children":[{"children":[{"offset":2,"type":"percent","value":"%"},{"children":[{"children":[{"offset":4,"type":"sequence"},{"children":[{"children":[{"offset":4,"type":"base_identifier","value":"y"}],"type":"identifier"}],"type":"atom"}],"type":"sequence"}],"type":"unary"}],"type":"sequence"},{"offset":5,"type":"sequence"}],"type":"sequence"}],"type":"sequence"}],"type":"product"},{"offset":5,"type":"sequence"}],"type":"sequence"}],"type":"sum"},{"offset":5,"type":"sequence"}],"type":"sequence"}],"type":"comparison"},{"offset":5,"type":"sequence"}],"type":"sequence"}],"type":"equality"},{"offset":5,"type":"sequence"}],"type":"sequence"}],"type":"conjunction"},{"offset":5,"type":"sequence"}],"type":"sequence"}],"type":"disjunction"}'
	test_json_output
}

@test "parser: product, with some multiplications" {
	declare -r INPUT="x * y * z"
	declare -r OUTPUT='{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"offset":0,"type":"sequence"},{"children":[{"children":[{"offset":0,"type":"base_identifier","value":"x"}],"type":"identifier"}],"type":"atom"}],"type":"sequence"}],"type":"unary"},{"children":[{"children":[{"offset":2,"type":"star","value":"*"},{"children":[{"children":[{"offset":4,"type":"sequence"},{"children":[{"children":[{"offset":4,"type":"base_identifier","value":"y"}],"type":"identifier"}],"type":"atom"}],"type":"sequence"}],"type":"unary"}],"type":"sequence"},{"children":[{"children":[{"offset":6,"type":"star","value":"*"},{"children":[{"children":[{"offset":8,"type":"sequence"},{"children":[{"children":[{"offset":8,"type":"base_identifier","value":"z"}],"type":"identifier"}],"type":"atom"}],"type":"sequence"}],"type":"unary"}],"type":"sequence"},{"offset":9,"type":"sequence"}],"type":"sequence"}],"type":"sequence"}],"type":"sequence"}],"type":"product"},{"offset":9,"type":"sequence"}],"type":"sequence"}],"type":"sum"},{"offset":9,"type":"sequence"}],"type":"sequence"}],"type":"comparison"},{"offset":9,"type":"sequence"}],"type":"sequence"}],"type":"equality"},{"offset":9,"type":"sequence"}],"type":"sequence"}],"type":"conjunction"},{"offset":9,"type":"sequence"}],"type":"sequence"}],"type":"disjunction"}'
	test_json_output
}

@test "parser: product, with an one multiplication, a division and a modulo" {
	declare -r INPUT="x * y / z % w"
	declare -r OUTPUT='{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"offset":0,"type":"sequence"},{"children":[{"children":[{"offset":0,"type":"base_identifier","value":"x"}],"type":"identifier"}],"type":"atom"}],"type":"sequence"}],"type":"unary"},{"children":[{"children":[{"offset":2,"type":"star","value":"*"},{"children":[{"children":[{"offset":4,"type":"sequence"},{"children":[{"children":[{"offset":4,"type":"base_identifier","value":"y"}],"type":"identifier"}],"type":"atom"}],"type":"sequence"}],"type":"unary"}],"type":"sequence"},{"children":[{"children":[{"offset":6,"type":"slash","value":"/"},{"children":[{"children":[{"offset":8,"type":"sequence"},{"children":[{"children":[{"offset":8,"type":"base_identifier","value":"z"}],"type":"identifier"}],"type":"atom"}],"type":"sequence"}],"type":"unary"}],"type":"sequence"},{"children":[{"children":[{"offset":10,"type":"percent","value":"%"},{"children":[{"children":[{"offset":12,"type":"sequence"},{"children":[{"children":[{"offset":12,"type":"base_identifier","value":"w"}],"type":"identifier"}],"type":"atom"}],"type":"sequence"}],"type":"unary"}],"type":"sequence"},{"offset":13,"type":"sequence"}],"type":"sequence"}],"type":"sequence"}],"type":"sequence"}],"type":"sequence"}],"type":"product"},{"offset":13,"type":"sequence"}],"type":"sequence"}],"type":"sum"},{"offset":13,"type":"sequence"}],"type":"sequence"}],"type":"comparison"},{"offset":13,"type":"sequence"}],"type":"sequence"}],"type":"equality"},{"offset":13,"type":"sequence"}],"type":"sequence"}],"type":"conjunction"},{"offset":13,"type":"sequence"}],"type":"sequence"}],"type":"disjunction"}'
	test_json_output
}

# it tests an alternation parser with rules that begin a same way
@test "parser: product, with a function call" {
	declare -r INPUT="x() * y"
	declare -r OUTPUT='{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"offset":0,"type":"sequence"},{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"offset":0,"type":"base_identifier","value":"x"}],"type":"identifier"},{"offset":1,"type":"nothing"}],"type":"sequence"},{"offset":2,"type":"sequence"}],"type":"sequence"},{"offset":2,"type":"nothing"}],"type":"sequence"}],"type":"function_call"}],"type":"atom"}],"type":"sequence"}],"type":"unary"},{"children":[{"children":[{"offset":4,"type":"star","value":"*"},{"children":[{"children":[{"offset":6,"type":"sequence"},{"children":[{"children":[{"offset":6,"type":"base_identifier","value":"y"}],"type":"identifier"}],"type":"atom"}],"type":"sequence"}],"type":"unary"}],"type":"sequence"},{"offset":7,"type":"sequence"}],"type":"sequence"}],"type":"sequence"}],"type":"product"},{"offset":7,"type":"sequence"}],"type":"sequence"}],"type":"sum"},{"offset":7,"type":"sequence"}],"type":"sequence"}],"type":"comparison"},{"offset":7,"type":"sequence"}],"type":"sequence"}],"type":"equality"},{"offset":7,"type":"sequence"}],"type":"sequence"}],"type":"conjunction"},{"offset":7,"type":"sequence"}],"type":"sequence"}],"type":"disjunction"}'
	test_json_output
}
