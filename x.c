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

int main(int argc, char *argv[])
{
	char x[1];
	char *format = "\\x%.2x";

	// stdin
	while(read(0, x, sizeof(x))>0) {

		// ascii printable character range
		if (*x > 0x19 && *x < 0x7f) {
			putc(*x, stdout);
		}
		else {
			switch (*x) {
				// chars outside of the normal ascii range that
				// it's okay to print
				case 0x09: // \t
				case 0x0a: // \n
				case 0x0b: // \v
				case 0x0d: // \r
				case 0x1b: // \033, \x1b, \e, ansi code
					putc(*x, stdout);
					break;

				default:
					// otherwise print it in the \x12 style
					printf(format, (0xffffff00 ^ *x));
					break;
			}
		}
	}

	return 0;
}