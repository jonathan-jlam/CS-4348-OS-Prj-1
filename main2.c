
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h> 


int toMem[2];
int toCPU[2];


struct Package {
	int instruction;
	int opcode;
	int operand;
}

void mem(char filename[]) {

    char message[100];
	sprintf(message, "Hello from the parent!\n");
    write(toCPU[1], message, 100);

	//char message2[100];
	read(toMem[0], message, 100);
	printf("The parent got BACK: %s\n", message);

    FILE *fp = fopen(filename, "r");
    char line[100];
	int memory[2000];

	int i = 0;
	//char *token;

    while (fgets(line, 100, fp)) {
		//token = strtok(line, " ");
		//printf("Token: %s\n", token);
		int instruction = atoi(line);
		//printf("Token in int: %d\n", instruction);
		memory[i] = instruction;
		i++;
    }

	/*
	for (int k = 0; k < 10; k++) {
		printf("%d\n", memory[k]);
	}*/
	int address;
	//wait(NULL);
	while(read(toMem[0], &address, sizeof(address))) {
		
		struct Package instruction_package;
		instruction_package.instruction = memory[address];
		
		switch(instruction_package.instruction) {
			
		}
		int instruction = memory[address];
		write(toCPU[1], &instruction, sizeof(instruction));
		if (instruction == 50) {
			break;
		}

		switch(instruction) {
			case 23:
				read(toMem[0], &address, sizeof(address));
				instruction = memory[address];
				write(toCPU[1], &instruction, sizeof(instruction));
				read(toMem[0], &address, sizeof(address));

		}

	}

}


void CPU() {

    char receive[100];
    read(toCPU[0], receive, 100);
    fprintf(stderr, "The CPU got: %s\n", receive);
	write(toMem[1], "Hello from the child!", 100);

	

	int PC = 0;
	int SP = 999;
	int IR;
	int AC;
	int X;
	int Y;
	int timer;

	int operand;


	write(toMem[1], &PC, sizeof(PC));

	
	while(read(toCPU[0], &IR, sizeof(IR))) {
		
		switch(IR) {
			
			case 1:
				PC++;
				write(toMem[1], &PC, sizeof(PC));
				read(toCPU[0], &AC, sizeof(AC));
				break;
			case 9:
				PC++;
				write(toMem[1], &PC, sizeof(PC));
				read(toCPU[0], &operand, sizeof(operand));
				if (operand == 1) {
					printf("%d", AC);
				} else {
					printf("%c", AC);
				}
				break;
			case 23:
				PC++;
				write(toMem[1], &PC, sizeof(PC));
				read(toCPU[0], &operand, sizeof(operand));
				write(toMem[
				
		}

		printf("Instruction got: %d\n", IR);
		if (IR == 10) {
			int nextval;
			PC++;
			write(toMem[1], &PC, sizeof(PC));
			read(toCPU[0], &nextval, sizeof(nextval));
			printf("The nextval was: %d.\n", nextval);
		
		}
		if (IR == 50) {
			break;
		}
		PC++;
		write(toMem[1], &PC, sizeof(PC));
	}



}

int main(int argc, char* argv[]) {
    
    if (pipe(toMem) < 0 || pipe(toCPU) < 0) {
        write(STDERR_FILENO, "Pipe failed\n", 12);
        exit(1);
    }


	if (argc < 2) {
		fprintf(stderr, "Improper Usage: <program> <filename>\n");
		exit(1);
	}
	

    switch(fork()) {
        case -1: 
            write(STDERR_FILENO, "Fork failed\n", 12);
            exit(2);

        case 0:
			CPU();
			break;

        default: ;         
            char filename[100];
            strcpy(filename, argv[1]);
		    mem(filename);
			
    }




   
}
