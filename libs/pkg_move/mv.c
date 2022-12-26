#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include "../prints/prints.h"
char file_buffer[1024];

long getsize(char *filename){
    struct stat sb;
    if (stat(filename, &sb) == -1) {
        perror("stat");
        return -1;
    }
    return sb.st_size;
}
// Mover paquetes hacia carpeta de destino, se necesita una funcion callback para mostrar el progreso
// Funcion callback, archivo a mover, destino
int move(callback func_callback, char *src, char *dest, int debug, int progress){
    /* Accedo al fichero de origen */
    char file_buffer[2024];
    FILE *src1, *dest1;
    int cantidad;
    if ((src1 = fopen(src, "rb")) == NULL)
    {
      printd("No existe el paquete",debug);
      return 1;
    }
    /* Y ahora al de destino */
    if ((dest1 = fopen(dest, "wb")) == NULL){
      printd("No se pudo crear el nuevo paquete",debug);
      return 2;
    }
    long total = getsize(src);
    /* Mientras quede algo que leer */
    if (progress == 1){
        printf("[AVISO] Copiar mostrado el progreso puede hacer que la copia se vuelva mas lenta de lo normal\n");
        for (int x = 0; total>x; x++)
        {
            /* Leo datos: cada uno de 1 byte, todos los que me caben */
            cantidad = fread( file_buffer, 1, sizeof(file_buffer), src1);
            /* Escribo tantos como haya leído */
            fwrite(file_buffer, 1, cantidad, dest1);
            func_callback(x,total);
        }
    } else {
            while (! feof(src1))
            {
                /* Leo datos: cada uno de 1 byte, todos los que me caben */
                cantidad = fread( file_buffer, 1, sizeof(file_buffer), src1);
                /* Escribo tantos como haya leído */
                fwrite(file_buffer, 1, cantidad, dest1);
            }
    }
    /* Cierro los ficheros */
    fclose(src1);
    fclose(dest1);
    return 0;
}

//find move a file with progress