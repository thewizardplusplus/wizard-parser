load "../common/io_test"

declare -gra OPTIONS=("--stdin")

@test "parser: conjunction, with an one conjunction sign" {
	declare -r INPUT="x and y"
	declare -r OUTPUT='{
		"type": "conjunction",
		"children": [
			{"type": "identifier", "value": "x"},
			{"type": "identifier", "value": "y"}
		]
	}'
	io_test
}

@test "parser: conjunction, with some (two) conjunction signs" {
	declare -r INPUT="x and y and z"
	declare -r OUTPUT='{
		"type": "conjunction",
		"children": [
			{"type": "identifier", "value": "x"},
			{"type": "identifier", "value": "y"},
			{"type": "identifier", "value": "z"}
		]
	}'
	io_test
}

@test "parser: conjunction, with some (three) conjunction signs" {
	declare -r INPUT="x and y and z and w"
	declare -r OUTPUT='{
		"type": "conjunction",
		"children": [
			{"type": "identifier", "value": "x"},
			{"type": "identifier", "value": "y"},
			{"type": "identifier", "value": "z"},
			{"type": "identifier", "value": "w"}
		]
	}'
	io_test
}

@test "parser: disjunction, with an one disjunction sign" {
	declare -r INPUT="x or y"
	declare -r OUTPUT='{
		"type": "disjunction",
		"children": [
			{"type": "identifier", "value": "x"},
			{"type": "identifier", "value": "y"}
		]
	}'
	io_test
}

@test "parser: disjunction, with some (two) disjunction signs" {
	declare -r INPUT="x or y or z"
	declare -r OUTPUT='{
		"type": "disjunction",
		"children": [
			{"type": "identifier", "value": "x"},
			{"type": "identifier", "value": "y"},
			{"type": "identifier", "value": "z"}
		]
	}'
	io_test
}

@test "parser: disjunction, with some (three) disjunction signs" {
	declare -r INPUT="x or y or z or w"
	declare -r OUTPUT='{
		"type": "disjunction",
		"children": [
			{"type": "identifier", "value": "x"},
			{"type": "identifier", "value": "y"},
			{"type": "identifier", "value": "z"},
			{"type": "identifier", "value": "w"}
		]
	}'
	io_test
}
