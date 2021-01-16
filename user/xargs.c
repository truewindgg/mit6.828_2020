#include "kernel/types.h"
#include "user/user.h"
#include "kernel/param.h"

void main(int argc, char** argv){
    char *exe = argv[1];
    char line[MAXARG];
    int p = 0;
    int ret_read = -1;
    for(int i=0; i+1<argc; ++i){
        argv[i] = argv[i+1];
    }
    argv[argc-1] = line;
    while(ret_read != 0){
        while(p<MAXARG && (ret_read = read(0, line+p, 1))==1 && *(line+p)!='\n'){
           ++p;
        }
        if(p!=0 && p<MAXARG){
            //fprintf(1,"read line : %s.\n", line);
            *(line+p) = 0;
            if(fork()==0){
                //fprintf(1, "fork sucessfully.\n");
                if(exec(exe, argv) != 0){
                    fprintf(1, "exec %s fail.\n", argv[1]);
                }
                exit(0);
            }
        } 
        p = 0;
    }
    wait(0);
    exit(0);
}
