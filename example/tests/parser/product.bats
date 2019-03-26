load "../common/common"

declare -gra OPTIONS=("--stdin" "--target" "cst")

@test "parser: product, with an one multiplication" {
	declare -r INPUT="x * y"
	declare -r OUTPUT='{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"offset":0,"type":"identifier","value":"x"}],"type":"atom"}],"type":"sequence"}],"type":"unary"},{"offset":2,"type":"star","value":"*"},{"children":[{"children":[{"children":[{"offset":4,"type":"identifier","value":"y"}],"type":"atom"}],"type":"sequence"}],"type":"unary"}],"type":"sequence"}],"type":"product"}],"type":"sequence"}],"type":"sum"}'
	test_json_output
}

@test "parser: product, with an one division" {
	declare -r INPUT="x / y"
	declare -r OUTPUT='{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"offset":0,"type":"identifier","value":"x"}],"type":"atom"}],"type":"sequence"}],"type":"unary"},{"offset":2,"type":"slash","value":"/"},{"children":[{"children":[{"children":[{"offset":4,"type":"identifier","value":"y"}],"type":"atom"}],"type":"sequence"}],"type":"unary"}],"type":"sequence"}],"type":"product"}],"type":"sequence"}],"type":"sum"}'
	test_json_output
}

@test "parser: product, with an one modulo" {
	declare -r INPUT="x % y"
	declare -r OUTPUT='{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"offset":0,"type":"identifier","value":"x"}],"type":"atom"}],"type":"sequence"}],"type":"unary"},{"offset":2,"type":"percent","value":"%"},{"children":[{"children":[{"children":[{"offset":4,"type":"identifier","value":"y"}],"type":"atom"}],"type":"sequence"}],"type":"unary"}],"type":"sequence"}],"type":"product"}],"type":"sequence"}],"type":"sum"}'
	test_json_output
}

@test "parser: product, with some multiplications" {
	declare -r INPUT="x * y * z"
	declare -r OUTPUT='{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"offset":0,"type":"identifier","value":"x"}],"type":"atom"}],"type":"sequence"}],"type":"unary"},{"offset":2,"type":"star","value":"*"},{"children":[{"children":[{"children":[{"offset":4,"type":"identifier","value":"y"}],"type":"atom"}],"type":"sequence"}],"type":"unary"},{"offset":6,"type":"star","value":"*"},{"children":[{"children":[{"children":[{"offset":8,"type":"identifier","value":"z"}],"type":"atom"}],"type":"sequence"}],"type":"unary"}],"type":"sequence"}],"type":"product"}],"type":"sequence"}],"type":"sum"}'
	test_json_output
}

@test "parser: product, with an one multiplication, a division and a modulo" {
	declare -r INPUT="x * y / z % w"
	declare -r OUTPUT='{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"offset":0,"type":"identifier","value":"x"}],"type":"atom"}],"type":"sequence"}],"type":"unary"},{"offset":2,"type":"star","value":"*"},{"children":[{"children":[{"children":[{"offset":4,"type":"identifier","value":"y"}],"type":"atom"}],"type":"sequence"}],"type":"unary"},{"offset":6,"type":"slash","value":"/"},{"children":[{"children":[{"children":[{"offset":8,"type":"identifier","value":"z"}],"type":"atom"}],"type":"sequence"}],"type":"unary"},{"offset":10,"type":"percent","value":"%"},{"children":[{"children":[{"children":[{"offset":12,"type":"identifier","value":"w"}],"type":"atom"}],"type":"sequence"}],"type":"unary"}],"type":"sequence"}],"type":"product"}],"type":"sequence"}],"type":"sum"}'
	test_json_output
}

# it tests the alternation parser with rules that begin the same way
@test "parser: product, with a function call" {
	declare -r INPUT="x() * y"
	declare -r OUTPUT='{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"children":[{"offset":0,"type":"identifier","value":"x"}],"type":"sequence"}],"type":"function_call"}],"type":"atom"}],"type":"sequence"}],"type":"unary"},{"offset":4,"type":"star","value":"*"},{"children":[{"children":[{"children":[{"offset":6,"type":"identifier","value":"y"}],"type":"atom"}],"type":"sequence"}],"type":"unary"}],"type":"sequence"}],"type":"product"}],"type":"sequence"}],"type":"sum"}'
	test_json_output
}
