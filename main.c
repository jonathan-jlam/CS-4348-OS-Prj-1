
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>



int toMem[2];
int toCPU[2];


void mem() {

    char message[] = "HELLO FROM THE PARENT!";
    write(toCPU[1], message, 100);
	read(toMem[0], message, 100);
	printf("The parent got BACK: %s\n", message);
}


void CPU() {

    char receive[100];
    read(toCPU[0], receive, 100);
    fprintf(stderr, "The CPU got: %s\n", receive);
	write(toMem[1], "Hello from the child!", 100);
}

int main(int argc, char* argv[]) {
    
    if (pipe(toMem) < 0 || pipe(toCPU) < 0) {
        write(STDERR_FILENO, "Pipe failed\n", 12);
        exit(1);
    }

	if (argc < 2) {
		fprintf(stderr, "Improper Usage: <program> <filename>");
		exit(1);
	}

    switch(fork()) {
        case -1: 
            write(STDERR_FILENO, "Fork failed\n", 12);
            exit(2);

        case 0:
			CPU();
			break;

        default:           
		   mem();
			
			
    }




   


   
}
