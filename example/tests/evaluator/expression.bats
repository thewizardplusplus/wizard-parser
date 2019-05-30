load "../common/common"

declare -gra OPTIONS=("--stdin" "--precision" "6")

@test "evaluator: expression, with a minus and a multiplication" {
	declare -r INPUT="-5 * 12"
	declare -r OUTPUT="-60"
	test_text_output
}

@test "evaluator: expression, with a minus, a multiplication and a grouping" {
	declare -r INPUT="-(5 * 12)"
	declare -r OUTPUT="-60"
	test_text_output
}

@test "evaluator: expression, with a multiplication and an addition" {
	declare -r INPUT="5 * 12 + 23"
	declare -r OUTPUT="83"
	test_text_output
}

@test "evaluator: expression, with a multiplication, an addition and a grouping" {
	declare -r INPUT="5 * (12 + 23)"
	declare -r OUTPUT="175"
	test_text_output
}
