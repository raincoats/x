#include "x.h"

/*
 *  html.c
 *  ~~~~~~
 *  
 *  url-style character escaper for 'x'
 *  started 31 august 2016
 *
 *  you can probably guess what this does. yep, it changes, say,
 *      ' = '' UNION ALL SELECT NULL
 *  to a more url friendly version.
 *      %27+%3D+%27%27+UNION+ALL+SELECT+NULL
 *
 *
 */

/*
 *  the gross if statement in url_unsafe() is the printable ascii characters
 *  that php's urlencode() escapes. too lazy to look up the RFC for which
 *  characters in urls have to be escaped, you see.
 *  
 *  here's the rub:
 *
 *      <?php
 *      for ($i=0x20; $i<0x7f; $i++) {
 *          echo urlencode(chr($i))."\n";
 *      };
 *
 *  then just grep for '%' and you get the ranges.
 *  
 */
int url_unsafe(int c)
{
	if (((c > 0x20) && (c < 0x2d)) || (c == 0x2f)
	   || ((c > 0x39) && (c < 0x41))
	   || ((c > 0x5a) && (c < 0x5f))
	   || (c == 0x60))
		return true;

	if ((c > 0x7a) || (c < 0x20))
		return true;

	return false;
}

void url_encode(char *fmt, int c)
{
	if (c == ' ')
		putchar('+');
	else if (esc_all || url_unsafe(c))
		printf(fmt, c);
	else
		putchar(c);
}
