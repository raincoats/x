#!/bin/bash
# test script for 'x'

function test_x {
	count=$(($count+1))
	answer=$1; shift
	str=$1; shift
	flags="$@"

	result=$(printf -- "%s" "$str" | ./x $flags)
	result_sum=$(printf -- "%s" "$result" | sha1sum | awk '{ print $1 }')

	if [[ $result_sum = $answer ]]; then
		printf "\033[38;5;040m[+]\033[m test passed: %s\n" "$count"
	else
		printf "\033[38;5;196m[!]\033[m test failed: %s\n" "$count"
		printf "\033[38;5;196m[!]\033[m expected: %s\n" "$answer"
		printf "\033[38;5;196m[!]\033[m      got: %s\n" "$result_sum"
	fi
}


count=0

test_x '768f12a6e076435972e25647c9c4fefcb183613b' '12345' -a
test_x 'f9643dd2eeaa7bc071325e53129f604aa8a36a6e' $'\r\n\r\n' -a
test_x '8ada6e3198df61ecf6a6385bac2d1beaaf4e3a07' $'\r\n\v\t' -urt
test_x 'dd5c7d2946740badcedd42f1d24708791b49073e' $'\r\n\v\t'
test_x '5aa36381afcf3428f1a0f6585f6e9194ea86eded' $'hello ?!@' -s
test_x 'c5a5b93b729cf0b834cb1e5e2c7fe1c9a5745d6f' $'hello ?!@' -ua

