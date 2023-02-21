
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h> 
#include <time.h>

int toMem[2];
int toCPU[2];


void mem(char filename[]) {

	/*
    char message[100];
	sprintf(message, "Hello from the parent!\n");
    write(toCPU[1], message, 100);

	read(toMem[0], message, 100);
	printf("The parent got BACK: %s\n", message);

	
	*/
    FILE *fp = fopen(filename, "r");
    char line[512];
	int memory[2000];

	int i = 0;
	//char *token;

    while (fgets(line, 512, fp) != NULL) {
		
		if (line[0] == '\n' || (line[0] != '0' && atoi(line) == 0)) {
			continue;
		}
		

		int instruction;
		

		if (line[0] == '.') {
			char* first_char_removed = line+1;
			i = atoi(first_char_removed);
			i--;
		} else {
			instruction = atoi(line);
			memory[i] = instruction;
		}

		i++;

    }

	//for (int p = 17; p < 18; p++) {
	//
	//	printf("%d\n", memory[p]);
	//}


	/*
	for (int k = 0; k < 10; k++) {
		printf("%d\n", memory[k]);
	}*/
	int address;
	//wait(NULL);
	while(read(toMem[0], &address, sizeof(address))) {
		
		
		int instruction = memory[address];
	//	printf("Address: %d || Instruction: %d\n", address, instruction);
		write(toCPU[1], &instruction, sizeof(instruction));

		switch(instruction) {
			case 1:
				read(toMem[0], &address, sizeof(address));
				instruction = memory[address];
				write(toCPU[1], &instruction, sizeof(instruction));
				break;
			case 4:
				read(toMem[0], &address, sizeof(address));
				instruction = memory[address];
				write(toCPU[1], &instruction, sizeof(instruction));
				read(toMem[0], &address, sizeof(address));
				instruction = memory[address];
				write(toCPU[1], &instruction, sizeof(instruction));
				break;
			case 5:
				read(toMem[0], &address, sizeof(address));
				instruction = memory[address];
				write(toCPU[1], &instruction, sizeof(instruction));
				read(toMem[0], &address, sizeof(address));
				instruction = memory[address];
				write(toCPU[1], &instruction, sizeof(instruction));
				break;
			case 6:
				read(toMem[0], &address, sizeof(address));
				instruction = memory[address];
				write(toCPU[1], &instruction, instruction);
				break;
			case 9:		
				read(toMem[0], &address, sizeof(address));
				instruction = memory[address];
				write(toCPU[1], &instruction, sizeof(instruction));
				break;
			case 20:
				read(toMem[0], &address, sizeof(address));
				instruction = memory[address];
				write(toCPU[1], &instruction, sizeof(instruction));
				break;
			case 21:
				read(toMem[0], &address, sizeof(address));
				if (address == -1) {
					read(toMem[0], &address, sizeof(address));
					instruction = memory[address];
					write(toCPU[1], &instruction, sizeof(instruction));
				} else {
					break;										
				}
				break;
			case 22:
				read(toMem[0], &instruction, sizeof(instruction)); //case 22
				if (instruction == -1) { //got a -1 which means we are branching
					read(toMem[0], &address, sizeof(address));
					instruction = memory[address];
					write(toCPU[1], &instruction, sizeof(instruction));
				} 
				break;
			case 23:
				read(toMem[0], &address, sizeof(address));
				instruction = memory[address];
				write(toCPU[1], &instruction, sizeof(instruction));
				read(toMem[0], &instruction, sizeof(instruction));
				read(toMem[0], &address, sizeof(address));
				memory[address] = instruction;
				break;
			case 24:
				read(toMem[0], &instruction, sizeof(instruction));
				address = memory[instruction];
				write(toCPU[1], &address, sizeof(address));
				break;
			case 27:
				read(toMem[0], &instruction, sizeof(instruction));
				read(toMem[0], &address, sizeof(address));
				memory[address] = instruction;
				break;
			case 28:
				read(toMem[0], &address, sizeof(address));
				instruction = memory[address];
				write(toCPU[1], &instruction, sizeof(instruction));
				break;
			case 50:
				exit(0);
			
			
			


		}

	}

}


void CPU() {

	srand(getpid() + getuid() + time(NULL));
	/*
    char receive[100];
    read(toCPU[0], receive, 100);
    fprintf(stderr, "The CPU got: %s\n", receive);
	write(toMem[1], "Hello from the child!", 100);
*/
	

	int PC = 0;
	int SP = 1000;
	int IR;
	int AC;
	int X;
	int Y;
	int timer;
	int end = 0;

	int operand;


	write(toMem[1], &PC, sizeof(PC));


	while(read(toCPU[0], &IR, sizeof(IR))) {
		
//		printf("PC at beg: %d\n", PC);
		switch(IR) {
			
			case 1:
				PC++;
				write(toMem[1], &PC, sizeof(PC));
				read(toCPU[0], &AC, sizeof(AC));
				break;
			case 4:
				PC++;
				write(toMem[1], &PC, sizeof(PC));
				read(toCPU[0], &operand, sizeof(operand));
				operand += X;
				write(toMem[1], &operand, sizeof(operand));
				read(toCPU[0], &AC, sizeof(AC));
				break;
			
			case 5:
				PC++;
				write(toMem[1], &PC, sizeof(PC));
				read(toCPU[0], &operand, sizeof(operand));
				operand += Y;
				write(toMem[1], &operand, sizeof(operand));
				read(toCPU[0], &AC, sizeof(AC));
				break;
			case 6:
				operand = SP + X;
				write(toMem[1], &operand, sizeof(operand));
				read(toCPU[0], &AC, sizeof(AC));
				break;
			case 8:
				AC = (int) ((rand() % 99) + 1);
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
			case 10:
				AC += X;
				break;
			case 11:
				AC += Y;
				break;
			case 14:
				X = AC;
				break;
			case 15:
				AC = X;
				break;
			case 16:
				Y = AC;
				break;
			case 20:
				PC++;
				write(toMem[1], &PC, sizeof(PC));
				read(toCPU[0], &PC, sizeof(PC));
				PC--;
				break;
			case 21:
				PC++;
				if (AC==0) {
					operand = -1;
					write(toMem[1], &operand, sizeof(operand));
					write(toMem[1], &PC, sizeof(PC));
					read(toCPU[0], &PC, sizeof(PC));
					PC--;
				} else {

					operand = -2;
					write(toMem[1], &operand, sizeof(operand));
				}
				break;
			case 22:
				if (AC != 0) {
					operand = -1;
					write(toMem[1], &operand, sizeof(operand));
					PC+=1;
					write(toMem[1], &PC, sizeof(PC));
					read(toCPU[0], &PC, sizeof(PC));
					PC--;	
				} else {
					operand = -2;
					write(toMem[1], &operand, sizeof(operand));
				}
				break;
			case 23:
				PC++;
				write(toMem[1], &PC, sizeof(PC));
				read(toCPU[0], &operand, sizeof(operand));
				PC++;
				write(toMem[1], &PC, sizeof(PC));//return address
				SP--;
				write(toMem[1], &SP, sizeof(SP)); // stack pointer
				PC = operand-1;
				break;
			case 24:
				write(toMem[1], &SP, sizeof(SP));
				read(toCPU[0], &PC, sizeof(PC));
				PC--;
				SP++;
				break;
			case 25:
				X++;
				break;
			case 26:
				X--;
				break;
			case 27:
				write(toMem[1], &AC, sizeof(AC));
				SP--;
				write(toMem[1], &SP, sizeof(SP));
				break;
			case 28:	
				write(toMem[1], &SP, sizeof(SP));
				read(toCPU[0], &AC, sizeof(AC));
				SP++;
				break;
			case 50:
				exit(0);
			
			
				
		}
		/*
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
		*/
	

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
			
			//char filename[100];
			//strcpy(filename, argv[1]);
			//mem(filename);
        default:;         
            char filename[100];
            strcpy(filename, argv[1]);
		    mem(filename);

			//CPU();
			//break;
			
    }




   
}
