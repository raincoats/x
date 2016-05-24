/*
 * x.c
 * ~~~~~
 *
 * hex dumpy thing that only escapes unprintables
 * by @reptar_xl
 *
 * 7 mar 2016
 *
 * i don't know c very well, as you can tell...
 *
 */
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>


char x[1];

int ch         = 0;
int filter_all = 0;
int allow_tabs = 0;
int allow_cr   = 0;
int allow_lf   = 0;
int allow_ansi = 0;





int needs_escaping(int i)
{
	if (filter_all) {
		return 1;
	}

	if ((i > 0x19) && (i < 0x7f))
		return 0;

	switch (i) {
		case 0x0d:
			return allow_cr;
		case 0x0a:
			return allow_lf;
		case 0x09:
			return allow_tabs;
		case 0x0b:
			return allow_tabs;
		case 0x1b:
			return allow_ansi;
	}

	return 1;
}

int usage(void)
{
	dprintf(2, "%s", "wow\n");
	exit(2);
}


int main(int argc, char *argv[])
{
	// i basically stole this getopts thing from the Darwin ping source code
	while ((ch = getopt(argc, argv, "hatnr" )) != -1)
	{
		switch(ch) {

			case 'h':
				usage();
				break;

			case 'a':
				filter_all = 1;
				break;

			case 't':
				allow_tabs = 1;
				break;

			case 'n':
				allow_lf = 1;
				break;

			case 'r':
				allow_cr = 1;
				break;

			default:
				dprintf(2, "%s: %s: %s\n", argv[0], "unknown option", optarg);
				break;
		}
	}


	while(read(0, x, sizeof(x))>0) {

		if (needs_escaping(*x)) {
			// for some reason, some characters come out escaped with a bunch of
			// f's in front of them, like \xffffffa4 \xffffffee. so this just 
			// cuts those f's off.
			printf("\\%.2x", ((0xffffff00 | *x) ^ 0xffffff00));
		}
		else {
			putchar(*x);
		}
	}
	return 0;
}