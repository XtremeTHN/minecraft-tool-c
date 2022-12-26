#ifndef _PKGMV
#define _PKGMV
typedef void (*callback)(int, long);
int move(callback func_callback, char *src, char *dest, int debug, int progress);

#include "mv.c"
#endif