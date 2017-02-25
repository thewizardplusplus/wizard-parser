load "../common/io_test"

declare -gra OPTIONS=("--stdin")

@test "parser: comparison, with an one less sign" {
	declare -r INPUT="x < y"
	declare -r OUTPUT='{
		"type": "comparison",
		"children": [
			{"type": "identifier", "value": "x"},
			{"type": "less", "value": "<"},
			{"type": "identifier", "value": "y"}
		]
	}'
	io_test
}

@test "parser: comparison, with an one less-or-equal sign" {
	declare -r INPUT="x <= y"
	declare -r OUTPUT='{
		"type": "comparison",
		"children": [
			{"type": "identifier", "value": "x"},
			{"type": "less_or_equal", "value": "<="},
			{"type": "identifier", "value": "y"}
		]
	}'
	io_test
}

@test "parser: comparison, with an one great sign" {
	declare -r INPUT="x > y"
	declare -r OUTPUT='{
		"type": "comparison",
		"children": [
			{"type": "identifier", "value": "x"},
			{"type": "great", "value": ">"},
			{"type": "identifier", "value": "y"}
		]
	}'
	io_test
}

@test "parser: comparison, with an one great-or-equal sign" {
	declare -r INPUT="x >= y"
	declare -r OUTPUT='{
		"type": "comparison",
		"children": [
			{"type": "identifier", "value": "x"},
			{"type": "great_or_equal", "value": ">="},
			{"type": "identifier", "value": "y"}
		]
	}'
	io_test
}

@test "parser: comparison, with some less signs" {
	declare -r INPUT="x < y < z"
	declare -r OUTPUT='{
		"type": "comparison",
		"children": [
			{"type": "identifier", "value": "x"},
			{"type": "less", "value": "<"},
			{"type": "identifier", "value": "y"},
			{"type": "less", "value": "<"},
			{"type": "identifier", "value": "z"}
		]
	}'
	io_test
}

@test "parser: comparison, with one less, less-or-equal, great and great-or-equal signs" {
	declare -r INPUT="x < y <= z > w >= t"
	declare -r OUTPUT='{
		"type": "comparison",
		"children": [
			{"type": "identifier", "value": "x"},
			{"type": "less", "value": "<"},
			{"type": "identifier", "value": "y"},
			{"type": "less_or_equal", "value": "<="},
			{"type": "identifier", "value": "z"},
			{"type": "great", "value": ">"},
			{"type": "identifier", "value": "w"},
			{"type": "great_or_equal", "value": ">="},
			{"type": "identifier", "value": "t"}
		]
	}'
	io_test
}
