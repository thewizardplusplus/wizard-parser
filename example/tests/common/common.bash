function test_json_output() {
	declare -r output="`echo -n "$INPUT" \
		| "${COMMAND[@]}" "${OPTIONS[@]}" \
		| jq -cSM ""
	`"
	declare -r expected_output="`echo "$OUTPUT" | jq -cSM ""`"
	[[ "$output" == "$expected_output" ]]
}

function test_text_output() {
	if [[ "$1" != "stderr" ]]; then
		declare -r output="`echo -n "$INPUT" | "${COMMAND[@]}" "${OPTIONS[@]}"`"
		[[ "$output" == "$OUTPUT" ]]
	else
		declare -r output="`echo -n "$INPUT" | "${COMMAND[@]}" "${OPTIONS[@]}" 2>&1`"
		[[ "$output" == "$OUTPUT" ]]
	fi
}
