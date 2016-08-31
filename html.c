#include "x.h"

/*
 *  html.c
 *  ~~~~~~
 *
 *  html-style character escaper for 'x'
 *  started 31 august 2016
 *
 *  takes a character and escapes it like &amp; (or &#x26; if -N passed)
 *
 */

int html_unsafe(int c);
int html_named_entity(int c);

void html_encode(char *fmt, int c)
{
	// see if it has an entity name first, then if it
	// doesn't, see if it's ascii
	if ((! no_named) && html_named_entity(c))
		return;
	else if (esc_all || (! is_ascii(c)) || html_unsafe(c))
		printf(fmt, c);
	else
		putchar(c);
}

int html_unsafe(int c)
{
	// got these from doing php htmlentities() on the ascii range
	if ((c == '"') || (c == '&') || (c == '<') || (c == '>'))
		return true;
	else
		return false;
}

int html_named_entity(int c)
{
	char *name;

	switch (c) {
		case '\x22': name = "quot";    break; // "
		case '\x26': name = "amp";     break; // &
		case '\x27': name = "apos";    break; // '
		case '\x3C': name = "lt";      break; // <
		case '\x3E': name = "gt";      break; // >
		case '\xA0': name = "nbsp";    break; // 
		case '\xA1': name = "iexcl";   break; // ¡
		case '\xA2': name = "cent";    break; // ¢
		case '\xA3': name = "pound";   break; // £
		case '\xA4': name = "curren";  break; // ¤
		case '\xA5': name = "yen";     break; // ¥
		case '\xA6': name = "brvbar";  break; // ¦
		case '\xA7': name = "sect";    break; // §
		case '\xA8': name = "uml";     break; // ¨
		case '\xA9': name = "copy";    break; // ©
		case '\xAA': name = "ordf";    break; // ª
		case '\xAB': name = "laquo";   break; // «
		case '\xAC': name = "not";     break; // ¬
		case '\xAD': name = "shy";     break; // 
		case '\xAE': name = "reg";     break; // ®
		case '\xAF': name = "macr";    break; // ¯
		case '\xB0': name = "deg";     break; // °
		case '\xB1': name = "plusmn";  break; // ±
		case '\xB2': name = "sup2";    break; // ²
		case '\xB3': name = "sup3";    break; // ³
		case '\xB4': name = "acute";   break; // ´
		case '\xB5': name = "micro";   break; // µ
		case '\xB6': name = "para";    break; // ¶
		case '\xB7': name = "middot";  break; // ·
		case '\xB8': name = "cedil";   break; // ¸
		case '\xB9': name = "sup1";    break; // ¹
		case '\xBA': name = "ordm";    break; // º
		case '\xBB': name = "raquo";   break; // »
		case '\xBC': name = "frac14";  break; // ¼
		case '\xBD': name = "frac12";  break; // ½
		case '\xBE': name = "frac34";  break; // ¾
		case '\xBF': name = "iquest";  break; // ¿
		case '\xC0': name = "Agrave";  break; // À
		case '\xC1': name = "Aacute";  break; // Á
		case '\xC2': name = "Acirc";   break; // Â
		case '\xC3': name = "Atilde";  break; // Ã
		case '\xC4': name = "Auml";    break; // Ä
		case '\xC5': name = "Aring";   break; // Å
		case '\xC6': name = "AElig";   break; // Æ
		case '\xC7': name = "Ccedil";  break; // Ç
		case '\xC8': name = "Egrave";  break; // È
		case '\xC9': name = "Eacute";  break; // É
		case '\xCA': name = "Ecirc";   break; // Ê
		case '\xCB': name = "Euml";    break; // Ë
		case '\xCC': name = "Igrave";  break; // Ì
		case '\xCD': name = "Iacute";  break; // Í
		case '\xCE': name = "Icirc";   break; // Î
		case '\xCF': name = "Iuml";    break; // Ï
		case '\xD0': name = "ETH";     break; // Ð
		case '\xD1': name = "Ntilde";  break; // Ñ
		case '\xD2': name = "Ograve";  break; // Ò
		case '\xD3': name = "Oacute";  break; // Ó
		case '\xD4': name = "Ocirc";   break; // Ô
		case '\xD5': name = "Otilde";  break; // Õ
		case '\xD6': name = "Ouml";    break; // Ö
		case '\xD7': name = "times";   break; // ×
		case '\xD8': name = "Oslash";  break; // Ø
		case '\xD9': name = "Ugrave";  break; // Ù
		case '\xDA': name = "Uacute";  break; // Ú
		case '\xDB': name = "Ucirc";   break; // Û
		case '\xDC': name = "Uuml";    break; // Ü
		case '\xDD': name = "Yacute";  break; // Ý
		case '\xDE': name = "THORN";   break; // Þ
		case '\xDF': name = "szlig";   break; // ß
		case '\xE0': name = "agrave";  break; // à
		case '\xE1': name = "aacute";  break; // á
		case '\xE2': name = "acirc";   break; // â
		case '\xE3': name = "atilde";  break; // ã
		case '\xE4': name = "auml";    break; // ä
		case '\xE5': name = "aring";   break; // å
		case '\xE6': name = "aelig";   break; // æ
		case '\xE7': name = "ccedil";  break; // ç
		case '\xE8': name = "egrave";  break; // è
		case '\xE9': name = "eacute";  break; // é
		case '\xEA': name = "ecirc";   break; // ê
		case '\xEB': name = "euml";    break; // ë
		case '\xEC': name = "igrave";  break; // ì
		case '\xED': name = "iacute";  break; // í
		case '\xEE': name = "icirc";   break; // î
		case '\xEF': name = "iuml";    break; // ï
		case '\xF0': name = "eth";     break; // ð
		case '\xF1': name = "ntilde";  break; // ñ
		case '\xF2': name = "ograve";  break; // ò
		case '\xF3': name = "oacute";  break; // ó
		case '\xF4': name = "ocirc";   break; // ô
		case '\xF5': name = "otilde";  break; // õ
		case '\xF6': name = "ouml";    break; // ö
		case '\xF7': name = "divide";  break; // ÷
		case '\xF8': name = "oslash";  break; // ø
		case '\xF9': name = "ugrave";  break; // ù
		case '\xFA': name = "uacute";  break; // ú
		case '\xFB': name = "ucirc";   break; // û
		case '\xFC': name = "uuml";    break; // ü
		case '\xFD': name = "yacute";  break; // ý
		case '\xFE': name = "thorn";   break; // þ
		case '\xFF': name = "yuml";    break; // ÿ
		default:
			return false;
	}

	printf("&%s;", name);
	return true;

}
