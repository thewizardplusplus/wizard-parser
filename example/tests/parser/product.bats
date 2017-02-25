load "../common/io_test"

declare -gra OPTIONS=("--stdin")

@test "parser: product, with an one multiplication" {
	declare -r INPUT="x * y"
	declare -r OUTPUT='{
		"type": "product",
		"children": [
			{"type": "identifier", "value": "x"},
			{"type": "star", "value": "*"},
			{"type": "identifier", "value": "y"}
		]
	}'
	io_test
}

@test "parser: product, with an one division" {
	declare -r INPUT="x / y"
	declare -r OUTPUT='{
		"type": "product",
		"children": [
			{"type": "identifier", "value": "x"},
			{"type": "slash", "value": "/"},
			{"type": "identifier", "value": "y"}
		]
	}'
	io_test
}

@test "parser: product, with an one modulo" {
	declare -r INPUT="x % y"
	declare -r OUTPUT='{
		"type": "product",
		"children": [
			{"type": "identifier", "value": "x"},
			{"type": "percent", "value": "%"},
			{"type": "identifier", "value": "y"}
		]
	}'
	io_test
}

@test "parser: product, with some multiplications" {
	declare -r INPUT="x * y * z"
	declare -r OUTPUT='{
		"type": "product",
		"children": [
			{"type": "identifier", "value": "x"},
			{"type": "star", "value": "*"},
			{"type": "identifier", "value": "y"},
			{"type": "star", "value": "*"},
			{"type": "identifier", "value": "z"}
		]
	}'
	io_test
}

@test "parser: product, with an one multiplication, a division and a modulo" {
	declare -r INPUT="x * y / z % w"
	declare -r OUTPUT='{
		"type": "product",
		"children": [
			{"type": "identifier", "value": "x"},
			{"type": "star", "value": "*"},
			{"type": "identifier", "value": "y"},
			{"type": "slash", "value": "/"},
			{"type": "identifier", "value": "z"},
			{"type": "percent", "value": "%"},
			{"type": "identifier", "value": "w"}
		]
	}'
	io_test
}

# it tests an alternation parser with rules that begin a same way
@test "parser: product, with a function call" {
	declare -r INPUT="x() * y"
	declare -r OUTPUT='{
		"type": "product",
		"children": [
			{
				"type": "function_call",
				"children": [{"type": "identifier", "value": "x"}]
			},
			{"type": "star", "value": "*"},
			{"type": "identifier", "value": "y"}
		]
	}'
	io_test
}
