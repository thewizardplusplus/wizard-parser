#!/usr/bin/env bash

set -e

declare tests_group="all"

declare -r script_name="`basename "$0"`"
# you can't wrap options variable in a command call (e.g. "declare" or
# "eval set --"), because it hides its exit code
options="`
	getopt \
		--name "$script_name" \
		--options "hg:" \
		--longoptions "help,group:" \
		-- "$@"
`"
eval set -- "$options"
while [[ "$1" != "--" ]]
do
	case "$1" in
		"-h" | "--help")
			echo "Usage:"
			echo "  $script_name -h | --help"
			echo "  $script_name [-g GROUP | --group GROUP]"
			echo
			echo "Options:"
			echo "  -h, --help               - show this message;"
			echo "  -g GROUP, --group GROUP  - set a group of used tests" \
				'(allowed: "lexer", "parser" or "all"; default: "all").'

			exit 0
			;;
		"-g" | "--group")
			case "$2" in
				"lexer")
					tests_group="lexer"
					;;
				"parser")
					tests_group="parser"
					;;
			esac

			# the additional shift for the option parameter
			shift
			;;
	esac

	shift
done

declare -r script_path="`dirname "$0"`"
declare -r example_command=("$script_path/../example")
case "$tests_group" in
	"lexer")
		COMMAND="${example_command[@]}" bats "$script_path"/lexer/*.bats
		;;
	"parser")
		COMMAND="${example_command[@]}" bats "$script_path"/parser/*.bats
		;;
	"all")
		COMMAND="${example_command[@]}" bats \
			"$script_path"/lexer/*.bats \
			"$script_path"/parser/*.bats

		;;
esac
