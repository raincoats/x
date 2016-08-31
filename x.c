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
#include "x.h"
#include "html.c"
#include "generic.c"
#include "url.c"

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
		"  -H   html encoding\n"
		"  -N   no named escapes, just char codes\n"
		"  -w   no whitespace (analogous to -tnrs)\n"
		"  -h   this lovely help\n"
	, argv0);
	exit(2);
}

void version()
{
	dprintf(2, "x, version %s\nhttps://github.com/raincoats/x\n", VERSION);
	exit(2);
}


int is_ascii(int c)
{
	if ((c > 0x20) && (c < 0x7f)) {
		return true;
	}
	return false;
}

int needs_escaping(int c)
{
	switch (c) {
		case '\r': return esc_cr;
		case '\n': return esc_lf;
		case '\t': return esc_tabs;
		case '\v': return esc_vtab;
		case '\e': return esc_ansi;
		case ' ':  return esc_space;
	}

	if (is_ascii(c))
		return false;

	return true;
}

int main(int argc, char *argv[])
{
	void (*encoder)(char *, int) = &generic_encode;
	char *fmt = "\\x%02x";

	unsigned int c;
	char biffer[8192];
	ssize_t len;

	int ch;

	while ((ch = getopt(argc, argv, "hHvatnrsiNwuo")) != -1)
	{
		switch(ch) {

			case 'h': usage(argv[0]);   break;
			case 'v': version();        break;
			case 't': esc_tabs  = true; break;
			case 'n': esc_lf    = true; break;
			case 'r': esc_cr    = true; break;
			case 's': esc_space = true; break;
			case 'i': esc_ansi  = true; break;
			case 'N': no_named  = true; break;
			case 'w':
				esc_cr    = true;
				esc_lf    = true;
				esc_feed  = true;
				esc_tabs  = true;
				esc_vtab  = true;
				esc_space = true;
				break;
			case 'a':
				esc_all = true;
				/*
				 *  holy crap. look at this goddamn cast. i want to print it out
				 *  and hang it on my wall. and it only took me 3 tries to get
				 *  right!
				 */ 
				encoder = (void(*))&printf;
				break;
			case 'u':
				encoder = &url_encode;
				fmt = "%%%02X";
				break;
			case 'o':
				encoder = &generic_encode;
				fmt = "\\%o";
				break;
			case 'H':
				encoder = &html_encode;
				fmt = "&#x%02X;";
				break;
		}
	}

	// woooo main loop
	while ((len = read(0, biffer, sizeof biffer)) > 0)
	{
		char *ptr = biffer;
		while (len --> 0)
		{
			memcpy(&c, ptr++, 1);
			(*encoder)(fmt, c);
		}
	}

	if (isatty(1))
		putchar('\n');

	return 0;
}

