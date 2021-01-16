#include "kernel/types.h"
#include "user/user.h"

void main(int argc, char *argv[]){
    if(argc < 2){
        printf("usage: sleep ticks\n");
        exit(1);
    }
    int ticks = atoi(argv[1]);
    if(ticks>10){
        exit(0);
    }
    fprintf(1, "sleep for %d ticks.\n", ticks);
    int stat = sleep(ticks);
    fprintf(1, "sleep status is %d.\n", stat);
    exit(0);
}
