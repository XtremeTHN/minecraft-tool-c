#ifndef _NEWCONF
#define _NEWCONF

int create_conf(char *f_conf, char *name, int debug);
static int init_handler(void* user, const char* section, const char* name, const char* value);
#include "cfg_funcs.c"
#endif