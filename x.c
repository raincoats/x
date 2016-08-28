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
#include <getopt.h>
#include <unistd.h>

#define VERSION "0.7"

unsigned int x[1];

int ch          = 0;
int filter_all  = 0;
int allow_space = 0;
int allow_tabs  = 0;
int allow_cr    = 0;
int allow_lf    = 0;
int allow_ansi  = 0;
int urlencode   = 0;
int php_escape  = 0;
int sh_escape   = 0;
int nonhex      = 0;


int needs_escaping(int i)
{
/*
 *  things in this function return 2 when they can be
 *  escaped with a backslash, like \' \" \( etc.
 *  thinking specifically about shell use/php use.
 */
	if (nonhex) {
		switch (i) {
			case '$':
			case '`':
			case '"':
			case '{':
			case '}':
			case '&':
			case '!':
			case '*':
			case '=':
			case ';':
			case '(':
			case ')':
			case '#':
			case '[':
			case ']':
			case '^':
			case ' ':
			case '~':
			case '|':
			case '?':
			case '<':
			case '>':
			case '\\':
			case '\'':
				return 2;
		}
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
		"  -t   escape tabs\n"
		"  -n   escape newlines\n"
		"  -r   escape carriage returns\n"
		"  -s   escape spaces\n"
		"  -i   escape ansi\n"
		"  -u   urlencode\n"
		"  -o   octal\n"
		"  -e   avoid hex where possible\n"
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
	char *fmt = "\\x%.2x";

	while ((ch = getopt(argc, argv, "hvatnrsiuoe")) != -1)
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
			case 'i':
				allow_ansi = 1;
				break;
			case 'u':
				urlencode = 1;
				fmt = "%%%02X";
				break;
			case 'o':
				fmt = "\\0%02o";
				break;			
			case 'e':
				nonhex = 1;
				break;
			default:
				dprintf(2, "%s: %s: %s\n", argv[0], "unknown option", optarg);
				break;
		}
	}

	while(read(0, x, 1) > 0)
	{
		int esc = needs_escaping(*x);

		if (esc || filter_all)
		{
			if (nonhex && esc == 2) {
				printf("\\%s", (unsigned char *)x);
			}
			else {
				printf(fmt, *x);				
			}
		}
		else {
			putchar(*x);
		}
	}

	// if the last char was a newline, don't double it
	if (isatty(1) && (*x != '\n'))
		putchar('\n');

	return 0;
}