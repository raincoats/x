# x

## a hex dumper thing that only escapes unprintable characters

`x` only escapes characters that aren’t printable ASCII. Like:

    cat /proc/self/environ | x
    USER=root\x00LOGNAME=root\x00HOME=/root\x00

    printf -- $'hello 😍!!\n\t—how are you?\n' | ./x
    hello \xf0\x9f\x98\x8d!!
	    \xe2\x80\x94how are you?


