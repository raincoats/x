all:
	gcc -Wall -fstack-protector-strong -O2 -march=native -o x x.c

debug:
	gcc -Wall -fbuiltin -ggdb3 -g3 -O0 -o x x.c

install: all
	cp -f x /usr/local/bin/x

debug_install: debug
	cp -f x /usr/local/bin/x

uninstall:
	rm -f /usr/local/bin/x

clean:
	rm -f x

