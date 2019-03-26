load "../common/common"

declare -gra OPTIONS=("--stdin")

@test "evaluator: product, with an one multiplication" {
	declare -r INPUT="5 * 12"
	declare -r OUTPUT="60.000000"
	test_text_output
}

@test "evaluator: product, with an one division" {
	declare -r INPUT="5 / 12"
	declare -r OUTPUT="0.416667"
	test_text_output
}

@test "evaluator: product, with an one modulo" {
	declare -r INPUT="12 % 5"
	declare -r OUTPUT="2.000000"
	test_text_output
}

@test "evaluator: product, with some multiplications" {
	declare -r INPUT="5 * 12 * 23"
	declare -r OUTPUT="1380.000000"
	test_text_output
}
