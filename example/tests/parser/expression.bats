load "../common/io_test"

declare -gra OPTIONS=("--stdin")

@test "parser: expression, with a minus and a multiplication" {
	declare -r INPUT="-x * y"
	declare -r OUTPUT='{
		"type": "product",
		"children": [
			{
				"type": "unary",
				"children": [
					{"type": "minus", "value": "-"},
					{"type": "identifier", "value": "x"}
				]
			},
			{"type": "star", "value": "*"},
			{"type": "identifier", "value": "y"}
		]
	}'
	io_test
}

@test "parser: expression, with a minus, a multiplication and a grouping" {
	declare -r INPUT="-(x * y)"
	declare -r OUTPUT='{
		"type": "unary",
		"children": [
			{"type": "minus", "value": "-"},
			{
				"type": "product",
				"children": [
					{"type": "identifier", "value": "x"},
					{"type": "star", "value": "*"},
					{"type": "identifier", "value": "y"}
				]
			}
		]
	}'
	io_test
}

@test "parser: expression, with a multiplication and an addition" {
	declare -r INPUT="x * y + z"
	declare -r OUTPUT='{
		"type": "sum",
		"children": [
			{
				"type": "product",
				"children": [
					{"type": "identifier", "value": "x"},
					{"type": "star", "value": "*"},
					{"type": "identifier", "value": "y"}
				]
			},
			{"type": "plus", "value": "+"},
			{"type": "identifier", "value": "z"}
		]
	}'
	io_test
}

@test "parser: expression, with a multiplication, an addition and a grouping" {
	declare -r INPUT="x * (y + z)"
	declare -r OUTPUT='{
		"type": "product",
		"children": [
			{"type": "identifier", "value": "x"},
			{"type": "star", "value": "*"},
			{
				"type": "sum",
				"children": [
					{"type": "identifier", "value": "y"},
					{"type": "plus", "value": "+"},
					{"type": "identifier", "value": "z"}
				]
			}
		]
	}'
	io_test
}

@test "parser: expression, with an addition and a less sign" {
	declare -r INPUT="x + y < z"
	declare -r OUTPUT='{
		"type": "comparison",
		"children": [
			{
				"type": "sum",
				"children": [
					{"type": "identifier", "value": "x"},
					{"type": "plus", "value": "+"},
					{"type": "identifier", "value": "y"}
				]
			},
			{"type": "less", "value": "<"},
			{"type": "identifier", "value": "z"}
		]
	}'
	io_test
}

@test "parser: expression, with an addition, a less sign and a grouping" {
	declare -r INPUT="x + (y < z)"
	declare -r OUTPUT='{
		"type": "sum",
		"children": [
			{"type": "identifier", "value": "x"},
			{"type": "plus", "value": "+"},
			{
				"type": "comparison",
				"children": [
					{"type": "identifier", "value": "y"},
					{"type": "less", "value": "<"},
					{"type": "identifier", "value": "z"}
				]
			}
		]
	}'
	io_test
}

@test "parser: expression, with a less sign and an equal sign" {
	declare -r INPUT="x < y == z"
	declare -r OUTPUT='{
		"type": "equality",
		"children": [
			{
				"type": "comparison",
				"children": [
					{"type": "identifier", "value": "x"},
					{"type": "less", "value": "<"},
					{"type": "identifier", "value": "y"}
				]
			},
			{"type": "equal", "value": "=="},
			{"type": "identifier", "value": "z"}
		]
	}'
	io_test
}

@test "parser: expression, with a less sign, an equal sign and a grouping" {
	declare -r INPUT="x < (y == z)"
	declare -r OUTPUT='{
		"type": "comparison",
		"children": [
			{"type": "identifier", "value": "x"},
			{"type": "less", "value": "<"},
			{
				"type": "equality",
				"children": [
					{"type": "identifier", "value": "y"},
					{"type": "equal", "value": "=="},
					{"type": "identifier", "value": "z"}
				]
			}
		]
	}'
	io_test
}

@test "parser: expression, with an equal sign and a conjunction sign" {
	declare -r INPUT="x == y and z"
	declare -r OUTPUT='{
		"type": "conjunction",
		"children": [
			{
				"type": "equality",
				"children": [
					{"type": "identifier", "value": "x"},
					{"type": "equal", "value": "=="},
					{"type": "identifier", "value": "y"}
				]
			},
			{"type": "identifier", "value": "z"}
		]
	}'
	io_test
}

@test "parser: expression, with an equal sign, a conjunction sign and a grouping" {
	declare -r INPUT="x == (y and z)"
	declare -r OUTPUT='{
		"type": "equality",
		"children": [
			{"type": "identifier", "value": "x"},
			{"type": "equal", "value": "=="},
			{
				"type": "conjunction",
				"children": [
					{"type": "identifier", "value": "y"},
					{"type": "identifier", "value": "z"}
				]
			}
		]
	}'
	io_test
}

@test "parser: expression, with a conjunction sign and a disjunction sign" {
	declare -r INPUT="x and y or z"
	declare -r OUTPUT='{
		"type": "disjunction",
		"children": [
			{
				"type": "conjunction",
				"children": [
					{"type": "identifier", "value": "x"},
					{"type": "identifier", "value": "y"}
				]
			},
			{"type": "identifier", "value": "z"}
		]
	}'
	io_test
}

@test "parser: expression, with a conjunction sign, a disjunction sign and a grouping" {
	declare -r INPUT="x and (y or z)"
	declare -r OUTPUT='{
		"type": "conjunction",
		"children": [
			{"type": "identifier", "value": "x"},
			{
				"type": "disjunction",
				"children": [
					{"type": "identifier", "value": "y"},
					{"type": "identifier", "value": "z"}
				]
			}
		]
	}'
	io_test
}
