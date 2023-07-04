#include "kernel/types.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
    if(argc != 1){
        printf("Error");
        exit(-1);
    }
    int p[2];
    pipe(p);
    char buf[128];
    char word = 'p';
    if(fork() == 0){
        printf("%d: received ping\n", getpid());
        read(p[0], buf, sizeof(buf));
        write(p[1], &word, 1);
        close(p[0]);
        close(p[1]);
        exit(0);
    }else{
        write(p[1], &word, 1);
        wait((int*) 0);
        printf("%d: received pong\n", getpid());
        read(p[0], buf, sizeof(buf));
        close(p[0]);
        close(p[1]);
        exit(0);
    }

    exit(0);
}