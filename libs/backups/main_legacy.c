#include <stdio.h>
#include "libs/parsers/arg/argparse.h"
#include "libs/parsers/conf/ini.h"
#include "libs/parsers/conf/nconf.h"
#include <stdbool.h>

static const char *const usages[] = {
    "minecraft [options] [[--] args]",
    "minecraft [options]",
    NULL,
};

int main(int argc, char *argv[]){
    bool inst = false;
    bool cconf = false;
    size_t bufsize = 32;
    size_t characters;
    char *buffer;
    const char *path = NULL;
    buffer = (char *)malloc(bufsize * sizeof(char));
    if (buffer == NULL){
        perror("No se pudo alocar un buffer");
        return 1;
    }
    struct argparse_option arguments[] = {
        OPT_HELP(),
        OPT_GROUP("Argumentos basicos"),
        OPT_BOOLEAN('i', "install", &path, "Instalar un paquete, sintaxis 'minecraft -i [shaderpack, resourcepack] [pack]'"),
        OPT_BOOLEAN('c', "create-conf", &cconf, "Crea un archivo de configuracion predeterminado"),
        OPT_END(),
    };
    struct argparse argparse;
    argparse_init(&argparse, arguments, usages, 0);
    argparse_describe(&argparse, "\nMinecraft tool creado por XtremeTHN, funcionalidades para mas comodidad", "\nSigue en desarrollo Minecraft Tool 0.0.1");
    argc = argparse_parse(&argparse, argc, argv);
    if (path != NULL){
        printf("Instalando...\n");
    }
    if (cconf != false){
        char *choice;
        printf("Carpeta raiz de minecraft: ");
        getline(&buffer, &bufsize,stdin);
        printf("%s", buffer);
        strcat(buffer, "\n");
        printf("Creando configuracion...\n");
        create_conf(buffer, "false\n","data.conf");
        return 0;
    }
    return 0;
}