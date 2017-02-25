load "../common/io_test"

declare -gra OPTIONS=("--stdin")

@test "parser: unary, with an one minus" {
	declare -r INPUT="-test"
	declare -r OUTPUT='{
		"type": "unary",
		"children": [
			{"type": "minus", "value": "-"},
			{"type": "identifier", "value": "test"}
		]
	}'
	io_test
}

@test "parser: unary, with an one negation" {
	declare -r INPUT="not test"
	declare -r OUTPUT='{
		"type": "unary",
		"children": [
			{"type": "base_identifier", "value": "not"},
			{"type": "identifier", "value": "test"}
		]
	}'
	io_test
}

@test "parser: unary, with some (two) minuses" {
	declare -r INPUT="--test"
	declare -r OUTPUT='{
		"type": "unary",
		"children": [
			{"type": "minus", "value": "-"},
			{"type": "minus", "value": "-"},
			{"type": "identifier", "value": "test"}
		]
	}'
	io_test
}

@test "parser: unary, with some (three) minuses" {
	declare -r INPUT="---test"
	declare -r OUTPUT='{
		"type": "unary",
		"children": [
			{"type": "minus", "value": "-"},
			{"type": "minus", "value": "-"},
			{"type": "minus", "value": "-"},
			{"type": "identifier", "value": "test"}
		]
	}'
	io_test
}

@test "parser: unary, with an one minus and a negation" {
	declare -r INPUT="-not test"
	declare -r OUTPUT='{
		"type": "unary",
		"children": [
			{"type": "minus", "value": "-"},
			{"type": "base_identifier", "value": "not"},
			{"type": "identifier", "value": "test"}
		]
	}'
	io_test
}
