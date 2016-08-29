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
int c_escape    = 0;


/*
 *  i'm calling them C escapes because i don't know what they're actually
 *  called. i'm talking about the escapes like \n instead of \x0a etc.
 */
int get_c_escape(int i)
{
	switch (i) {
		case '\r':
			return 'r';
		case '\n':
			return 'n';
		case '\t':
			return 't';
		case '\v':
			return 'v';
		case '\e':
			return 'e';
		case '\0':
			return '0';
	}
	return '?';
}

int needs_escaping(int i)
{
	/*
	 *  things in this function return 2 when they can be
	 *  escaped with a backslash, like \' \" \( etc.
	 *  thinking specifically about shell use/php use.
	 */
	if (nonhex) {
		switch (i) {
			case '$':  case '`':  case '"':  case '{':
			case '}':  case '&':  case '!':  case '*':
			case '=':  case ';':  case '(':  case ')':
			case '#':  case '[':  case ']':  case '^':
			case ' ':  case '~':  case '|':  case '?':
			case '<':  case '>':  case '\\': case '\'':
				return 2;
		}
	}

	/*
	 *  returning 3 means we change \x00 to \0, \x0a to \n, etc.
	 *  c style escapes.
	 */
	if (c_escape) {
		switch (i) {
			case '\r':
			case '\n':
			case '\t':
			case '\v':
			case '\e':
			case '\0':
				return 3;
		}		
	}

	/*
	 *  returning 0 means "escape it"
	 */
	if ((i > 0x20) && (i < 0x7f))
		return 0;

	switch (i) {
		case '\r':
			return allow_cr;
		case '\n':
			return allow_lf;
		case '\t':
			return allow_tabs;
		case '\v':
			return allow_tabs;
		case '\e':
			return allow_ansi;
		case ' ':
			return allow_space;
	}

	/*
	 *  and finally, returning 1 means it does not need escaping.
	 */
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
		"  -c   c-style escapes (\\r, \\n, \\v, etc)\n"
		"  -e   escape shell special characters\n"
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

	while ((ch = getopt(argc, argv, "hvatnrsiuoce")) != -1)
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
				fmt = "\\%o";
				break;			
			case 'e':
				nonhex = 1;
				break;
			case 'c':
				c_escape = 1;
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
			if (esc == 3) {
				// get C style escape character, like the n in '\n' for 0x0a
				*x = get_c_escape(*x);
			}
			if (esc == 2 || esc == 3) {
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