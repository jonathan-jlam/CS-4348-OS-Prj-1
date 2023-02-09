
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>


int toMem[2];
int toCPU[2];



int mem() {
    close(1);
    dup(toCPU[1]);

    close(0);
    dup(toMem[0]);

    for (int i = 0; i <= 1; i++) {
        close(toCPU[i]);
        close(toMem[i]);
    }

    char message[] = "HELLO FROM THE PARENT!";
    write(toCPU[1], "%s", message);
}


int CPU() {
    close(0);
    dup(toCPU[0]);

    close(1);
    dup(toMem[1]);

    for (int i = 0; i <= 1; i++) {
        close(toCPU[i]);
        close(toMem[i]);
    }

    char receive[100];
    read(toCPU[0], &receive, 100);
    sprintf(stderr, "%sNEWNEWNENW", receive);
}

int main() {
    
    if (pipe(toMem) < 0 || pipe(toCPU) < 0) {
        write(STDERR_FILENO, "Pipe failed\n", 12);
        exit(1);
    }

    switch(fork()) {
        case -1: 
            write(STDERR_FILENO, "Fork failed\n", 12);
            exit(2);

        case 0:
            mem();
        default:
            CPU();
    }




   


   
}