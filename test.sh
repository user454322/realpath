#!/bin/sh

set -o nounset

#
#----Constants
#
readonly GENERIC_EXIT_VAL='33'
readonly GREEN='\033[0;32m'
readonly INVALID_OPTION_ERROR='1'
readonly NAME_MAX='255'
readonly NO_COLOR='\033[0m'
readonly NOW="$(date +'%Y-%m-%d-%H.%M.%S')"
readonly PROGRAM_PATH='./realpath'
readonly PWD="$(ruby -e "puts File.realpath('$(pwd)')")"
readonly REAL_PATH_ERROR='2'
readonly RED='\033[0;31m'
readonly TEST_DIR="test_files_$NOW"


#
#----Functions
#

function assert_numbers_eq() {
	local readonly EXPECTED="$1"
	local readonly ACTUAL="$2"
	local readonly MSG="$3"
	local readonly EXIT_VAL="$4"

	if [ "$EXPECTED" -ne "$ACTUAL" ]; then
		echo " EXPECTED='$EXPECTED'  ACTUAL='$ACTUAL' $MSG"
		fail "$EXIT_VAL"
	fi
}

function fail() {
	echo " ${RED}FAILED${NO_COLOR}"
	if [ "x${1}" == "x" ]; then
	echo "here"
		exit "$GENERIC_EXIT_VAL"
	fi

	exit "$1"
}

function ok() {
	echo " ${GREEN}OK${NO_COLOR}"
}

function random_string() {
	if [ -c "/dev/urandom" ]; then
		grep -m 5 -ao '[a-zA-Z0-9]' /dev/urandom | tr '\n' '_' | sed s/_//g | colrm "$NAME_MAX"
	else
		date +"%s"
	fi
}

function test_no_option() {
	echo ""
	echo "Running test_no_option"

	local readonly RESULT=`./realpath`
	local readonly local EXIT_VAL="$?"

	if [ "$PWD" == "$RESULT" ];then
		ok
	else
		fail 100;
	fi

	assert_numbers_eq 0 "$EXIT_VAL" "" 101
}

function test_q_option_file_exists() {
	echo ""
	echo "Running test_q_option_file_exists"
	
	local readonly TFILE="${TEST_DIR}/testfile_test_q_option_file_exists"
	touch "$TFILE"	
	local RESULT="$($PROGRAM_PATH -q $TFILE)"
	local EXPECTED="${PWD}/${TFILE}"

	if [ "$EXPECTED" != "$RESULT" ];then
		fail 200
	fi

	local readonly QOPT_FILE="${TEST_DIR}/-q"
	$(touch -- "$QOPT_FILE")
	local readonly RESULT="$($PROGRAM_PATH -q $QOPT_FILE)"
	local readonly EXPECTED="${PWD}/${QOPT_FILE}"

	if [ "$EXPECTED" == "$RESULT" ];then
		ok
	else
		fail 201
	fi

	rm "$TFILE"
	rm -- "$QOPT_FILE"
}

function test_no_file() {
	echo ""
	echo "Running test_no_file"
	
	
	local readonly NO_FILE="${TEST_DIR}/$(random_string)"	
	./realpath "$NO_FILE"
	local EXIT_VAL="$?"
	assert_numbers_eq "$REAL_PATH_ERROR" "$EXIT_VAL" "test_no_file 301" 301
	
	./realpath -q "$NO_FILE"
	local EXIT_VAL="$?"
	assert_numbers_eq "$REAL_PATH_ERROR" "$EXIT_VAL" "test_no_file 302" 302

	ok

}

function test_usage {
	echo ""
	echo "Running test_usage"
	./realpath -h
	local EXIT_VAL="$?"
	assert_numbers_eq 0 "$EXIT_VAL" "test_usage 401" 401

	#Testing an invalid option
	./realpath -w
	local EXIT_VAL="$?"
	assert_numbers_eq "$INVALID_OPTION_ERROR" "$EXIT_VAL" "test_usage 402" 402

	ok
}

#
#----Execution
#
if [ ! -e "$PROGRAM_PATH" ]; then
	echo "'$PROGRAM_PATH' doesn't exist"
	exit 1;
fi

mkdir "$TEST_DIR"

test_no_option

test_q_option_file_exists

test_no_file

test_usage

\rm -fr "$TEST_DIR"

