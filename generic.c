#include "x.h"

/*
 *  generic.c
 *  ~~~~~~~~~
 *
 *  default character escaper for 'x'
 *  started 31 august 2016
 *
 *  generic_encode() takes a character and escapes it, if necessary, to a
 *  C-style escape (like \x0a, or \n / \012 depending on command line flags),
 *  and prints it to stdout.
 * 
 * 
 */

int c_named_escape(int c)
{
	char *name;

	switch (c) {
		case '\r': if (! esc_cr)   return false; name = "\\r"; break;
		case '\n': if (! esc_lf)   return false; name = "\\n"; break;
		case '\t': if (! esc_tabs) return false; name = "\\t"; break;
		case '\v': if (! esc_vtab) return false; name = "\\v"; break;
		case '\e': if (! esc_ansi) return false; name = "\\e"; break;
		case '\a': if (! esc_bell) return false; name = "\\a"; break;
		case '\b': if (! esc_bksp) return false; name = "\\b"; break;
		case '\f': if (! esc_feed) return false; name = "\\f"; break;
		default:
			return false;
	}

	assert(name != NULL);

	printf("%s", name);
	return true;
}


void generic_encode(char *fmt, int c)
{
	// if not (no named escapes) and (c_named_escape() printed the escape)
	if ((! no_named) && c_named_escape(c)) {
		return;
	}
	if (! needs_escaping(c)) {
		putchar(c);
	}
	else {
		printf(fmt, c);
	}
}


