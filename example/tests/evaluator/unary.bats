load "../common/common"

declare -gra OPTIONS=("--stdin" "--precision" "6")

@test "evaluator: unary, with an one minus" {
	declare -r INPUT="-5.12"
	declare -r OUTPUT="-5.12"
	test_text_output
}

@test "evaluator: unary, with some (two) minuses" {
	declare -r INPUT="--5.12"
	declare -r OUTPUT="5.12"
	test_text_output
}
