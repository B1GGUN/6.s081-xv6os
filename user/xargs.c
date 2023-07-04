#include "kernel/types.h"
#include "user/user.h"
#include "kernel/param.h"

int main(int argc, char* argv[]){

    if(argc < 2){
        printf("xargs : minum amount of args is 2!\n");
        exit(-1);
    }

    if(argc -1 >= MAXARG){
        printf("xargs : maxium amount of args is %d!\n", MAXARG);
        exit(-1);
    }

    char* x_args[MAXARG];

    for (int i = 1; i < argc; i++)
    {
        x_args[i-1] = argv[i];
    }

    char buf[512];
    int i = 0;
    int index = argc -1;
    int is_line_end = 0;
    while(read(0, &buf[i], sizeof(char))){
        if(buf[i] == '\n') is_line_end = 1;
        if(buf[i] == ' ' || buf[i] == '\n'){
            buf[i] = 0;
            x_args[index] = buf;
            index++;
            i = 0;
        }
        i++;

        if(is_line_end){
            is_line_end = 0;
            x_args[index] = 0;
            index = argc -1;
            int pid = fork();
            if (pid < 0)
            {
                printf("fork error!\n");
                exit(-1);
            }else if (pid == 0)
            {
                exec(x_args[0], x_args);
            }else{
                wait((int*)0);
            }            
        }
    }
    exit(0);
}