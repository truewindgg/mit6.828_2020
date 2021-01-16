#include "kernel/types.h"
#include "user/user.h"

void main(){
    int forkid = -1;
    int fp[2];
    if(pipe(fp) < 0){
        fprintf(2, "init pipe ERROR\n");
    }
    for(int i=2; i<=35; ++i){
        write(fp[1], &i, sizeof(int));
    }
    int number = 0;
    write(fp[1], &number, sizeof(int));
    while(fork() == 0){
        fprintf(1, "%d:forking\n", ++forkid);
        read(fp[0], &number, sizeof(int));
        fprintf(1, "prime %d\n", number);
        int empty = 1;
        int curNumber = number;
        while(read(fp[0], &number, sizeof(int)) && number!=0){
            if(number % curNumber != 0){
                empty = 0;             
                write(fp[1], &number, sizeof(int));
            }
        }
        if(empty){
            exit(0);
        }else{
            number = 0;
            write(fp[1], &number, sizeof(int));
        }
    }
    wait(0);
    fprintf(1, "%d:process closing...\n", forkid);
    exit(0);
}
