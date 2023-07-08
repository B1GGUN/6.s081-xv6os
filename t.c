#include <stdio.h>

__attribute__((constructor)) void hello(){
    printf("Hello szj.");
}

__attribute__((destructor)) void goodbye(){
    printf("Goodbye.");
}

int main(){

}