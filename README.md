# minecraft-tool-c
Proyecto hecho por mi, version original escrito en python pero decidí portearlo a C

## Archivos del repo
Documentacion de varios de los archivos

### build
El archivo compila con gcc y tiene la opcion de depurar con el sanitizador de google"Address"
```
./build [-d] [-ds]
```

### STATUS
Estado actual del proyecto (Solo es para que no se me olvide lo que estoy haciendo)

## Librerias
Solo una libreria esta hecha por terceros y la verdad la mayoria es para hacer ver el archivo main.c mas limpio

### cfg_funcs.h
Crea un archivo de configuracion, solo funciona para este programa ya que pues las funciones estan pensadas para funcionar aqui

### pkg_move
Copia un archivo hacia el destino, lee el contenido del origen y escribe hacia el destino. Acepta un callback y mas argumentos.
Por alguna extraña razón, si se le añade una barra de progreso o incluso solo añadiendo una funcion que muestre los bytes copiados se alenta como una tortuga, no se como arreglarlo asi que hize opcional el progreso

### prints.h
Funciones con printf, si el argumento quiet es 1 no muestra el mensaje, printd muestra un mensaje si el argumento debug es 1.

### split.h
Funciones varias para trabajar con rutas absolutas, como splitext (como en python) o iszip que confirma si es un archivo zip o no


