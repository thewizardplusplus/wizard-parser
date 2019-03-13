function test_json_output() {
	declare -r output="`echo -n "$INPUT" \
		| "${COMMAND[@]}" "${OPTIONS[@]}" \
		| jq -cSM ""
	`"
	declare -r expected_output="`echo "$OUTPUT" | jq -cSM ""`"
	[[ "$output" == "$expected_output" ]]
}

function test_error_output() {
	declare -r output="`echo -n "$INPUT" | "${COMMAND[@]}" "${OPTIONS[@]}" 2>&1`"
	[[ "$output" == "$OUTPUT" ]]
}
