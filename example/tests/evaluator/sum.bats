load "../common/common"

declare -gra OPTIONS=("--stdin" "--precision" "6")

@test "evaluator: sum, with an one addition" {
	declare -r INPUT="5 + 12"
	declare -r OUTPUT="17"
	test_text_output
}

@test "evaluator: sum, with an one subtraction" {
	declare -r INPUT="5 - 12"
	declare -r OUTPUT="-7"
	test_text_output
}

@test "evaluator: sum, with some (two) additions" {
	declare -r INPUT="5 + 12 + 23"
	declare -r OUTPUT="40"
	test_text_output
}
