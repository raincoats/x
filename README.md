# x

## a hex dumper thing that only escapes unprintable characters

`x`, by default, escapes characters that aren’t printable ASCII. Like:

    $ cat /proc/self/environ | x
    USER=root\x00LOGNAME=root\x00HOME=/root\x00

    $ printf -- $'hello 😍!!\n\t—how are you?\n' | ./x
    hello \xf0\x9f\x98\x8d!!
	    \xe2\x80\x94how are you?


However, you can also escape specific types of characters:

- `-a`, escape all characters
- `-t`, escape tabs
- `-n`, escape newlines
- `-r`, escape carriage returns
- `-s`, escape spaces
- `-i`, escape ansi


    $ echo "hello" | x -a
    \x68\x65\x6c\x6c\x6f\x0a

    $ echo $PS1 | x -i
    %{\x1b[38;5;228m%}%c %{\x1b[38;5;203m%}%#%{\x1b[m%}

You get the idea.
