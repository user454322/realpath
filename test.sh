#!/bin/sh

set -o errexit
set -o nounset

readonly PROGRAM_PATH="./realpath"
if [ ! -e "$PROGRAM_PATH" ]; then
	echo "'$PROGRAM_PATH' doesn't exist"
	exit 1;
fi

function test_no_option() {
	readonly RESULT="$($PROGRAM_PATH)"
	readonly PWD="$(pwd)"
	if [ "$PWD" == "$RESULT" ];then
		echo "OK"
	fi
	echo ">$RESULT<"
	echo ">$PWD<"
}

test_no_option

#no option  = pwd

#q_exist

#q_no_exist

#v

#h

#invalid -> usage

