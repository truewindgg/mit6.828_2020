#include "kernel/types.h"
#include "user/user.h"
#include "kernel/stat.h"
#include "kernel/fs.h"

int cmp(char *path, char *name){
    int n = strlen(path);
    int m = strlen(name);
    //fprintf(1, "compare %s and %s\n", path, name);
    if(n < m){
        return -1;
    }
    for(int i = n-m; i<n; ++i){
        if(path[i]!=name[i-n+m]){
            return -1;
        }
    }
    return 0;
}

void find(char* path, char* name){
    int fd;
    char buf[128], *p;
    struct dirent de;
    struct stat st;

    //fprintf(1, "looking name in : %s\n", path);

    if((fd = open(path, 0)) < 0){
        fprintf(2, "find : can't open : %s \n", path);
        fprintf(2, "len id : %d, fd is %d\n", strlen(path), fd);
        return;
    }

    if(fstat(fd, &st) < 0){
        fprintf(2, "find : can't get info of : %s \n", path);
        close(fd);
        return;
    }
    
    switch(st.type){
        case T_FILE:
            if(cmp(path, name)==0){
                fprintf(1, "%s\n", path);
            }
            break;
        case T_DIR:
            if(strlen(path) + 1 + DIRSIZ + 1 > sizeof buf){
                fprintf(2, "find: path too long.]\n");
                break;
            }
            strcpy(buf, path);
            p = buf + strlen(buf);
            *p++ = '/';
            while(read(fd, &de, sizeof(de))== sizeof(de)){
                if(de.inum == 0 )
                    continue;
                memmove(p, de.name, DIRSIZ);
                p[DIRSIZ] = 0;
                if(cmp(buf, ".")==0 || cmp(buf, "..")==0){
                    continue;
                }
                //fprintf(1, "recursion in path : %s\n", buf);
                find(buf, name);
            }
            break;
    }
    close(fd);
    return; 
}

void main(int argc, char** argv){
    if(argc < 3 || argc > 3){
        fprintf(2, "Usage: find [path] [name]\n");
        exit(1);
    }            
    //fprintf(1, "finding %s\n", argv[2]);
    find(argv[1], argv[2]);
    exit(0);
}
