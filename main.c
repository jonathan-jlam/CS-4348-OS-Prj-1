
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>

#define MAXLEN 100

int toMem[2];
int toCPU[2];



void mem() {

    char message[] = "HELLO FROM THE PARENT!";
	//printf("This is the file got by mem: %s\n", filename);
    write(toCPU[1], message, 100);
	read(toMem[0], message, 100);
	printf("The parent got BACK: %s\n", message);
	//int memory[2000];

/*
	FILE *fp = fopen(filename, "r");

	
	if (!fp) {
		fprintf(stderr, "Filename %s cannot be opened for reading.\n", filename);
		printf("%s", filename);
		exit(2);
	}

	printf("Opened %s for reading.\n", filename);
	char line[MAXLEN];
	while(fgets(line, MAXLEN, fp)) {
		printf("%s\n", line);
	}

	fclose(fp);
	*/
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
			//char filename[100];
		//	printf("%s", argv[1]);
		//	strcpy(filename, argv[1]);
           // mem(filename);
		   mem();
			
			
    }




   


   
}
