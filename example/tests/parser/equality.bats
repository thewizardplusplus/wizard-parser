load "../common/io_test"

declare -gra OPTIONS=("--stdin")

@test "parser: equality, with an one equal sign" {
	declare -r INPUT="x == y"
	declare -r OUTPUT='{
		"type": "equality",
		"children": [
			{"type": "identifier", "value": "x"},
			{"type": "equal", "value": "=="},
			{"type": "identifier", "value": "y"}
		]
	}'
	io_test
}

@test "parser: equality, with an one not-equal sign" {
	declare -r INPUT="x /= y"
	declare -r OUTPUT='{
		"type": "equality",
		"children": [
			{"type": "identifier", "value": "x"},
			{"type": "not_equal", "value": "/="},
			{"type": "identifier", "value": "y"}
		]
	}'
	io_test
}

@test "parser: equality, with some (two) equal signs" {
	declare -r INPUT="x == y == z"
	declare -r OUTPUT='{
		"type": "equality",
		"children": [
			{"type": "identifier", "value": "x"},
			{"type": "equal", "value": "=="},
			{"type": "identifier", "value": "y"},
			{"type": "equal", "value": "=="},
			{"type": "identifier", "value": "z"}
		]
	}'
	io_test
}

@test "parser: equality, with some (three) equal signs" {
	declare -r INPUT="x == y == z == w"
	declare -r OUTPUT='{
		"type": "equality",
		"children": [
			{"type": "identifier", "value": "x"},
			{"type": "equal", "value": "=="},
			{"type": "identifier", "value": "y"},
			{"type": "equal", "value": "=="},
			{"type": "identifier", "value": "z"},
			{"type": "equal", "value": "=="},
			{"type": "identifier", "value": "w"}
		]
	}'
	io_test
}

@test "parser: equality, with one equal and not-equal signs" {
	declare -r INPUT="x == y /= z"
	declare -r OUTPUT='{
		"type": "equality",
		"children": [
			{"type": "identifier", "value": "x"},
			{"type": "equal", "value": "=="},
			{"type": "identifier", "value": "y"},
			{"type": "not_equal", "value": "/="},
			{"type": "identifier", "value": "z"}
		]
	}'
	io_test
}
