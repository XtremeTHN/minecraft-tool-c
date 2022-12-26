#ifndef _SPLITNAME
#define _SPLITNAME
char *splitext(char *filename);
char *splitpath(char *path);
int exists(char *filename);
int iszip(char *ext);
#include "split.c"
#endif