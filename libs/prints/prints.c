#include <stdio.h>
void printd(char *msg, int debug){
    if (debug) {
        printf("[DEBUG] %s\n",msg);
    }
}

void printn(char *msg, int quiet){
    if (!quiet) {
        printf("[INFO] %s\n",msg);
    }
}

void print(char *msg, int quiet){
    if (!quiet) {
        printf("[INFO] %s",msg);
    }
}