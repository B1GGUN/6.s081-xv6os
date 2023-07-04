#include "kernel/types.h"
#include "user/user.h"

int get_first(int pipe[], int* first){
    if(read(pipe[0], first, sizeof(int))==sizeof(int)){
        printf("prime %d\n", *first);
        return 0;
    }else{
        return -1;
    }
}

void transmit_data(int lp[], int rp[], int first){
    int data;
    while(read(lp[0], &data, sizeof(int)) == sizeof(int)){
        if(data % first){
            write(rp[1], &data, sizeof(int));
        }
    }
    close(lp[0]);
    close(rp[1]);
}

void primes(int lp[2]){
    close(lp[1]);
    int first;
    if(get_first(lp, &first)==0){
        int rp[2];
        pipe(rp);
        transmit_data(lp, rp, first);
        if(fork() == 0){
            primes(rp);
        }else{
            close(rp[0]);
        }
    }

    wait((int*) 0);
    exit(0);
}

int
main(int argc, char *argv[]){
    int p[2];
    pipe(p);
    for(int i=2; i<=35; ++i){
        write(p[1], &i, sizeof(int));
    }

    if(fork() == 0){
        primes(p);
    }else{
        close(p[0]);
    }

    close(p[1]);
    wait((int*)0);
    exit(0);
}