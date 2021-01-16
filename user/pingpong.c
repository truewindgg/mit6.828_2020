#include "kernel/types.h"
#include "user/user.h"

void main(){
    int pp[2], cp[2]; 
    if(pipe(pp) < 0 || pipe(cp) < 0){
        fprintf(2, "pipe init ERROR.\n");
    }
    int pid = fork();
    if(pid == -1){
        fprintf(2, "fork ERROR.\n");
        exit(-1);
    }else if(pid == 0){
        char ping;
        read(pp[0], &ping, 1);
        fprintf(1, "%d: received ping\n", getpid());
        fprintf(1, "ping %c\n", ping);
        char pong = 'o';
        write(cp[1], &pong, 1);
    }else{
        char ping = 'i';
        write(pp[1], &ping, 1);
        char pong;
        read(cp[0], &pong, 1);
        fprintf(1, "%d: received pong\n", getpid());
        fprintf(1, "pong %c\n", pong);
    }
    exit(-1);
}
