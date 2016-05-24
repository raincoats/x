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


int needs_escaping(int i)
{
	
	if ((i > 0x19 && i < 0x7f)//   ascii printable character range
		|| (i == 0x09)  // \t
		|| (i == 0x0a)  // \n      chars outside of the normal ascii 
		|| (i == 0x0b)  // \v      range that it's okay to print
	 	|| (i == 0x0d)  // \r
	 	|| (i == 0x1b)  // \033, \x1b, \e, ansi code
	 	) {
		return 0;
	}

	return 1;
}

int main(int argc, char *argv[])
{
	char x[1];

	while(read(0, x, sizeof(x))>0) {

		if (needs_escaping(*x)) {
			// for some reason, some characters come out escaped with a bunch of
			// f's in front of them, like \xffffffa4 \xffffffee. so this just 
			// cuts those f's off.
			printf("\\%.2x", ((0xffffff00 | *x) ^ 0xffffff00));
		}
//		printf("\\x%.2x", );
		else
			putchar(*x);
	}
	return 0;
}