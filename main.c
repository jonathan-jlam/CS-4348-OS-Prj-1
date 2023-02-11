
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>



int toMem[2];
int toCPU[2];


void mem(filename) {

    char message[100];
	sprintf(message, "Hello from the parent!\n");
    write(toCPU[1], message, 100);

	//char message2[100];
	read(toMem[0], message, 100);
	printf("The parent got BACK: %s\n", message);

    FILE *fp = fopen(filename, "r");
    char line[100];
    while (fgets(line, 100, fp)) {
        printf("%s\n", line);
    }
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
            char filename[100];
            strcpy(filename, argv[1]);
		    mem(filename);
			
    }




   
}
