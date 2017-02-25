load "../common/io_test"

declare -gra OPTIONS=("--stdin")

@test "parser: sum, with an one addition" {
	declare -r INPUT="x + y"
	declare -r OUTPUT='{
		"type": "sum",
		"children": [
			{"type": "identifier", "value": "x"},
			{"type": "plus", "value": "+"},
			{"type": "identifier", "value": "y"}
		]
	}'
	io_test
}

@test "parser: sum, with an one subtraction" {
	declare -r INPUT="x - y"
	declare -r OUTPUT='{
		"type": "sum",
		"children": [
			{"type": "identifier", "value": "x"},
			{"type": "minus", "value": "-"},
			{"type": "identifier", "value": "y"}
		]
	}'
	io_test
}

@test "parser: sum, with some (two) additions" {
	declare -r INPUT="x + y + z"
	declare -r OUTPUT='{
		"type": "sum",
		"children": [
			{"type": "identifier", "value": "x"},
			{"type": "plus", "value": "+"},
			{"type": "identifier", "value": "y"},
			{"type": "plus", "value": "+"},
			{"type": "identifier", "value": "z"}
		]
	}'
	io_test
}

@test "parser: sum, with some (three) additions" {
	declare -r INPUT="x + y + z + w"
	declare -r OUTPUT='{
		"type": "sum",
		"children": [
			{"type": "identifier", "value": "x"},
			{"type": "plus", "value": "+"},
			{"type": "identifier", "value": "y"},
			{"type": "plus", "value": "+"},
			{"type": "identifier", "value": "z"},
			{"type": "plus", "value": "+"},
			{"type": "identifier", "value": "w"}
		]
	}'
	io_test
}

@test "parser: sum, with an one addition and a subtraction" {
	declare -r INPUT="x + y - z"
	declare -r OUTPUT='{
		"type": "sum",
		"children": [
			{"type": "identifier", "value": "x"},
			{"type": "plus", "value": "+"},
			{"type": "identifier", "value": "y"},
			{"type": "minus", "value": "-"},
			{"type": "identifier", "value": "z"}
		]
	}'
	io_test
}
