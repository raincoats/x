#ifndef FBJDGNFKDSLFDFNJDSMF
#define FBJDGNFKDSLFDFNJDSMF

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <getopt.h>
#include <unistd.h>
#include <stdbool.h>
#include <assert.h>

#define VERSION "0.9"

bool esc_all   = false;
bool esc_space = false;
bool esc_tabs  = false;
bool esc_vtab  = false;
bool esc_cr    = false;
bool esc_lf    = false;
bool esc_ansi  = false;
bool esc_bell  = false;
bool esc_bksp  = false;
bool esc_feed  = false;
bool no_named  = false;

int is_ascii(int c);
int needs_escaping(int c);
int html_named_entity(int c);

#endif //FBJDGNFKDSLFDFNJDSMF
