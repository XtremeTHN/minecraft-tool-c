#include <stdio.h>
#include <string.h>

char *splitext(char *filename) {
    char *dot = strrchr(filename, '.');
    if(!dot || dot == filename) return "";
    return dot + 1;
}

char *splitpath(char *path)
{
    char *fn;

    /* handle trailing '/' e.g. 
       path == "/home/me/myprogram/" */
    if (path[(strlen(path) - 1)] == '/')
        path[(strlen(path) - 1)] = '\0';

    (fn = strrchr(path, '/')) ? ++fn : (fn = path);

    return fn;
}

int exists(char *filename){
    FILE *filexd = fopen(filename,"rb");
    if (filexd == NULL){
        return 1;
    } else {
        fclose(filexd);
        return 0;
    }
}

int iszip(char *ext){
    int is_zip = strcmp(ext,"zip");
    if (is_zip == 1) return 1;
    return 0;
}