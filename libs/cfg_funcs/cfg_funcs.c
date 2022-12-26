#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "../prints/prints.h"

#ifndef MAX
#define MAX 1024
#endif

typedef struct {
    char *mine;
    bool auto_upd;
} configuration;

int create_conf(char *f_conf, char *name, int debug){
    printd("[INIPARSER]: Iniciando",debug);
    FILE *conf = fopen(name, "wt");
    char buffer[MAX];
    char *mine_path = "mine = ";
    char *auto_upd = "auto_upd = false";
    if (conf == NULL){
        printd("[INIPARSER] Error",debug);
        printd("[INIPARSER] Saliendo",debug);
        return 1;
    }
    
    memccpy(memccpy(buffer, mine_path, '\0', MAX) - 1, f_conf, '\0', MAX);
    fputs("[configs]\n", conf);
    fputs(buffer, conf);
    fputs(auto_upd, conf);
    fclose(conf);
    printd("[INIPARSER]: Completado",debug);
    return 0;
}

static int init_handler(void* user, const char* section, const char* name, const char* value)
{
    configuration* pconfig = (configuration*)user;

    #define MATCH(s, n) strcmp(section, s) == 0 && strcmp(name, n) == 0
    if (MATCH("configs", "auto_upd")) {
        pconfig->auto_upd = true;
    } else if (MATCH("configs", "mine")) {
        pconfig->mine = value;
    } else {
        return 0;  /* unknown section/name, error */
    }
    return 1;
}
