all:
	gcc -Wall -fstack-protector-strong -O2 -march=native x.c -o x

install:
	cp x /usr/local/bin/x

uninstall:
	[ -f 'x' ] && rm -f /usr/local/bin/x

clean:
	[ -f 'x' ] && rm -f x

