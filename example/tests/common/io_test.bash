function io_test() {
	declare -r output="`echo -n "$INPUT" \
		| "${COMMAND[@]}" "${OPTIONS[@]}" \
		| jq -cSM ""
	`"
	declare -r expected_output="`echo "$OUTPUT" | jq -cSM ""`"
	[[ "$output" == "$expected_output" ]]
}
