#include <stdio.h>
#include <string.h>
#include "libs/parsers/inih/ini.h"
#include "libs/parsers/inih/ini.c"
#include "libs/cfg_funcs/cfg_funcs.h"
#include "libs/pkg_move/mv.h"
#include "libs/progressbar/progress.h"
#include "libs/prints/prints.h"
#include "libs/split/split.h"
#include <argp.h>

// Documentacion

const char *argp_program_version = "0.0.1";
const char *argp_program_bug_address = "<nigthmaresans2@gmail.com>";

static char doc[] = "Minecraft Utility -- Herramienta de Minecraft para automatizar operaciones";
static char args_doc[] = " [-q] [-d] [-c] [-i LOCAL_PACKAGE] [-w PACKAGE_LINK] [-u PACKAGE]";

static struct argp_option options[] = {
    {"quiet", 'q', 0, 0, "No produce texto" },
    {"debug", 'd', 0, 0, "Produce texto extra" },
    {"progress", 'p', 0, 0, "Produce una barra de progreso en la copia de archivos"},
    {"resource", 'r', 0, 0, "0"},
    {"shader", 's', 0, 0, "0"},
    {"new-conf", 'c', 0, 0, "Crea un archivo de configuracion" },
    {"install", 'i', "NAME", 0, "Instala un paquete local" },
    {"install-from-web", 'w', "LINK", 0, "Instala un paquete desde un link proporcionado al paquete (link directo)" },
    {"uninstall", 'u', "NAME", 0, "Desinstala un paquete" },
    { 0 },
};

struct arguments {
    int quiet, debug, progress, nconf, install, shader, resource, uninstall;
    char *pkg_path;
};

static error_t
parse_opt (int key, char *arg, struct argp_state *state)
{
  /* Get the input argument from argp_parse, which we
     know is a pointer to our arguments structure. */
  struct arguments *arguments = state->input;

  switch (key)
    {
    case 'q':
      arguments->quiet = 1;
      break;
    case 'd':
      arguments->debug = 1;
      break;
    case 'p':
      arguments->progress = 1;
      break;
    case 'i':
      arguments->install = 1;
      arguments->pkg_path = arg;
      break;
    case 's':
      arguments->install = 1;
      break;
    case 'r':
      arguments->resource = 1;
      break;
    case 'u':
      arguments->pkg_path = arg;
      arguments->uninstall = 1;
      break;
    case 'c':
      arguments->nconf = 1;
      break;
    /*case ARGP_KEY_ARG:
      if (state->arg_num >= 2)
        argp_usage (state);

      arguments->args[state->arg_num] = arg;

      break;
    */

    /*case ARGP_KEY_END:
      if (state->arg_num < 2)
        // Not enough arguments.
        argp_usage (state);
      break;
    */
    default:
      return ARGP_ERR_UNKNOWN;
    }
  return 0;
}

static struct argp argp = { options, parse_opt, args_doc, doc };



int main(int argc, char *argv[]){
    //Indexando argumentos
    
    
    struct arguments arguments;

    /* Default values. */
    arguments.quiet = 0;
    arguments.debug = 0;
    arguments.progress = 0;
    arguments.resource = 0;
    arguments.shader = 0;
    arguments.nconf = 0;
    arguments.install = 0;
    arguments.uninstall = 0;
    arguments.pkg_path = "-";

    char *result[MAX];
    char *home = getenv("HOME");
    char *config_file = "/.config/mine_tool/data.conf";
    char *pkg_name;
    int error,is_zip;
    memccpy(memccpy(result, home, '\0', MAX) - 1, config_file, '\0', MAX);
    /* Parse our arguments; every option seen by parse_opt will
     be reflected in arguments. */
    argp_parse (&argp, argc, argv, 0, 0, &arguments);
    
    //Funciones principales
    if (arguments.install != 0){
      if (arguments.shader == 0 && arguments.resource == 0){
        printn("Especifica que quieres instalar con -s o -r, usa --help si tienes dudas",arguments.quiet);
        return 1;
      }
        configuration config;
        char *dest_buffer[MAX];
        char *full_minepath_buff[MAX];
        printd(arguments.pkg_path,arguments.debug);
        printd(result,arguments.debug);
        printn("Instalando...", arguments.quiet);
        if (exists(result) == 1){
            printn("No existe el archivo de configuracion, ejecuta el programa con el argumento -c",arguments.quiet);
            return 1;
        }
        if (exists(arguments.pkg_path) != 1) {
            if (ini_parse(result, init_handler, &config) < 0) {
              printd("No se pudo leer el archivo de configuracion", arguments.debug);
              return 1;
            }
            //Comprobando si es un tipo de archivo reconosible
            pkg_name = splitpath(arguments.pkg_path);
            printd(pkg_name,arguments.debug);
            is_zip = strcmp(splitext(pkg_name),"");
            if (is_zip == 1 || iszip(splitext(pkg_name)) == 1){
              printn("El archivo no es un paquete reconozible, debe de ser un archivo zip (*.zip)",arguments.quiet);
              return 1;
            }
            //Si lo es mover el archivo hacia la carpeta de minecraft, se identifica si el usuario quiere progreso o no, debido a que mostrarlo disminuye la velocidad de copia de archivos
            if (arguments.resource){
              memccpy(memccpy(dest_buffer, config.mine, '\0', MAX) - 1, "/shaderpacks/", '\0', MAX);
            } else if (arguments.shader) {
              memccpy(memccpy(dest_buffer, config.mine, '\0', MAX) - 1, "/resourcepacks/", '\0', MAX);
            }
            memccpy(memccpy(full_minepath_buff, dest_buffer, '\0', MAX) - 1, pkg_name, '\0', MAX);
            move(showprogress,arguments.pkg_path,dest_buffer,arguments.debug,arguments.progress);

            if (error == 1){
              printn("Ha habido un error al intentar mover el archivo, prueba a ejecutar con -d", arguments.quiet);
              return 1;
            }
            printn("Exito",arguments.quiet);
        } else {
            printn("El paquete especificado no existe",arguments.quiet);
            return 1;
        }
        return 0;
    }
    if (arguments.nconf != 0){
        char *choice;
        size_t bufsize = 64;
        size_t characters;
        char *buffer;
    
        buffer = (char *)malloc(bufsize * sizeof(char));
        if (buffer == NULL){
          printd("No se pudo alocar un buffer",arguments.debug);
          return 1;
        }
        printd(home,arguments.debug);
        
        
        printn("Ejecutando mkdir -p en la carpeta .config", arguments.quiet);
        system("mkdir -p $HOME/.config/mine_tool");
        
        print("Carpeta raiz de minecraft: ",arguments.quiet);
        getline(&buffer, &bufsize,stdin);
        printd(buffer, arguments.debug);
        strcat(buffer, "\n");
        printn("Creando configuracion...", arguments.quiet);
        create_conf(buffer,result,arguments.debug);
        free(buffer);
        return 0;
    }
    if (arguments.uninstall){
        printn("Funcion no implementada actualmente",arguments.quiet);
        return 0;
    }
    argp_help(&argp, stdout, ARGP_HELP_USAGE, "XD");
    return EXIT_SUCCESS;
}
