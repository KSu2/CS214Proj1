#include <stdlib.h>
#include <stdio.h>
#include "mymalloc.h"
#define MEMSIZE 4096

static char memory[MEMSIZE];

void *mymalloc(size_t size, char *file, int line){
	
	//do check for adjacent memory
	//eager coalescing method
	//2 bytes for "metadata" - 1 for boolean and 14 for integer representing its size
       	char *ptr = (char *) (memory); 
	//create void pointer p	
	void *p;
	
	//counting variables
	int i;
	int chunk_val = 2;
	//check if first chunk in memory is unitizialized
	if(memory[0] == 0) {
		//assign p to point to memory[2]
		p = (void *) (memory + 2);
		
		//use first 2 bytes of memory for the "metadata" (is it in use and 
		memory[0] = 1;
		memory[1] = size;
		for(i = 0; i < size; i++) {
			memory[i + 2] = chunk_val;
		}
		printf("value of byte before pointer: %d\n", *((char *)p - 1));
		printf("value of byte at pointer: %d\n", *((char *) p));
	}
	
	else {
		//check whether we have reached the end of the memory or not
		i = 1;
		while(i < MEMSIZE) {
			//add num of bytes to i equal to memory[i] which is the size of the current chunk
			if(memory[i] == 0){
				break;
			}
			else{
				chunk_val++;
				i = i + memory[i];
			}	
		}
		//assign p with the address of the start of the chunk being assigned
		p = (memory + (i + 1));
		i = i + 1;
	       	while(i < (size + 1)) {
			memory[i] = chunk_val;
		}	
			
	}
	return p;
}

void myfree(void* ptr, char *file, int line){
	//check if pointer is within the bounds of the addresses of the memory array 
	//this will mean the pointer is from malloc ow it is not
	if((char*)ptr >= (memory + 2) && (char*)ptr < (memory + MEMSIZE)){
		//check if address is pointing to an active chunk
		//error: double free
		if(*((char *) ptr - 2) == 0){
			printf("free: attempt to free already freed chunk (%s:%d)\n", file,line);
		}
		//check if pointer is not the beginning of a chunk
		//we initialize the payload of the first chunk as 2 
		//so the value of a pointer to the beginnign of any chunk should be >= 2
		else if((*((char *) ptr - 2)) > 1){
			printf("free: attempt to free pointer not pointing to start of chunk (%s:%d)\n", file, line);
		}
		else{
			printf("valid pointer\n");
                	*((int *)ptr - 2) = 0;
                	*((int *)ptr - 1) = 0;
                	
		}
		
	}
	//error: attempt to free non-block ptr
	else{
		printf("free: attempt to free non-block ptr (%s:%d)\n", file, line);
	}	
}
