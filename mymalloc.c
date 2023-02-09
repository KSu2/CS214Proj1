#include <stdlib.h>
#include <stdio.h>
#include "mymalloc.h"
#define MEMSIZE 4096

static char memory[MEMSIZE];

void *mymalloc(size_t size, char *file, int line){
	
	//do check for adjacent memory
	//eager coalescing method
	//2 bytes for "metadata" - 1 for boolean and 14 for integer representing its size
	printf("MYMALLOC! \n");
        
	printf("Beginning of memory %p\n", &(memory[0]));
	printf("End of memory %p\n", &(memory[4095]));
	//create void pointer p	
	void *p;
	//check if first chunk in memory is unitizialized
	if(memory[0] == 0) {
		//assign p the address of memory[0]
		p = memory;
		
		//use first 2 bytes of memory for the "metadata" (is it in use and 
		memory = 1;
		memory + 1 = size;
			
	}
	else {
		//check whether we have reached the end of the memory or not
		int i = 1;
		while(i < 4096) {
			//add num of bytes to i equal to memory[i] which is the size of the current chunk
			if(memory[i] == 0){
				break;
			}
			else{
				i = i + memory[i];
			}	
		}
		//assign p with the address of the start of the chunk being assigned
		p = (memory + (i - 1));
			
	}
	return p;
}

void myfree(void* ptr, char *file, int line){
	//check if pointer is within the bounds of the addresses of the memory array 
	//this will mean the pointer is from malloc ow it is not
	if((char*)ptr >= memory && (char*)ptr < (memory + MEMSIZE)){
		printf("valid pointer\n");
		//memory + (int*) ptr = 0;
		//memory + (int*) ptr + 1 = 0;
		//printf("value at memory[ptr] %d\n", memory + (int*)ptr);
		//printf("value at memory[ptr + 1] %d\n", memory + (int*)ptr + 1);
	}
	else{
		printf("invalid pointer\n");
	}
	
}
