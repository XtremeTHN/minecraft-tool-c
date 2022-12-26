#include <stdio.h>
#include <stdlib.h>

void showprogress(int pos, long max){
    int current_progress = pos / max * 100;
    printf("Progreso actual: %d\r",current_progress);
}