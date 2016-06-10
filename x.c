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

#define VERSION "0.2"

char x[1];

int ch          = 0;
int filter_all  = 0;
int allow_space = 0;
int allow_tabs  = 0;
int allow_cr    = 0;
int allow_lf    = 0;
int allow_ansi  = 0;


int needs_escaping(int i)
{
	if (filter_all) {
		return 1;
	}

	if ((i > 0x20) && (i < 0x7f))
		return 0;

	switch (i) {
		case 0x0d:
			return allow_cr;
		case 0x0a:
			return allow_lf;
		case 0x20:
			return allow_space;
		case 0x09:
			return allow_tabs;
		case 0x0b:
			return allow_tabs;
		case 0x1b:
			return allow_ansi;
	}

	return 1;
}


void usage(char *argv0)
{
	dprintf(2,
		"%s — hex escaper\n"
		"escapes only unprintable characters.\n"
		"works only on stdin, at the moment.\n\n"
		"  -a   escape all characters\n"
		"  -t   don’t escape tabs\n"
		"  -n   don’t escape newlines\n"
		"  -r   don’t escape carriage returns\n"
		"  -s   don’t escape spaces\n"
		"  -h   this lovely help\n"
	, argv0);
	exit(2);
}


void version()
{
	dprintf(2, "x, version %s\nhttps://github.com/raincoats/x\n", VERSION);
	exit(2);
}


int main(int argc, char *argv[])
{
	// i basically stole this getopts thing from the Darwin ping source code
	while ((ch = getopt(argc, argv, "hvatnrs" )) != -1)
	{
		switch(ch) {

			case 'h':
				usage(argv[0]);
				break;

			case 'v':
				version();
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

			case 's':
				allow_space = 1;
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
			printf("\\x%.2x", ((0xffffff00 | *x) ^ 0xffffff00));
		}
		else {
			putchar(*x);
		}
	}
	return 0;
}