#!/usr/bin/env bash

set -o errexit

declare tests_group="all"
declare -r script_name="$(basename "$0")"
# it's necessary to separate a variable declaration and its definition
# so that the declare command doesn't hide an exit code of a defining expression
declare options
options="$(
	getopt \
		--name "$script_name" \
		--options "hg:" \
		--longoptions "help,group:" \
		-- "$@"
)"
eval set -- "$options"
while [[ "$1" != "--" ]]; do
	case "$1" in
		"-h" | "--help")
			echo "Usage:"
			echo "  $script_name -h | --help"
			echo "  $script_name [-g GROUP | --group GROUP]"
			echo
			echo "Options:"
			echo "  -h, --help               - show this message;"
			echo "  -g GROUP, --group GROUP  - set a group of used tests" \
				'(allowed: "lexer", "parser", "errors" or "all"; default: "all").'

			exit 0
			;;
		"-g" | "--group")
			tests_group="$2"
			shift # additional shift for the option parameter
			;;
	esac

	shift
done

declare -r script_path="$(dirname "$0")"
declare -r example_command=("$script_path/../example")
case "$tests_group" in
	"lexer")
		COMMAND="${example_command[@]}" bats "$script_path"/lexer/*.bats
		;;
	"parser")
		COMMAND="${example_command[@]}" bats "$script_path"/parser/*.bats
		;;
	"errors")
		COMMAND="${example_command[@]}" bats "$script_path"/errors/*.bats
		;;
	"all")
		COMMAND="${example_command[@]}" bats \
			"$script_path"/lexer/*.bats \
			"$script_path"/parser/*.bats \
			"$script_path"/errors/*.bats
		;;
esac
