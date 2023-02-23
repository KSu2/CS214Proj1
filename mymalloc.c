#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "mymalloc.h"
#define MEMSIZE 4096

static char memory[MEMSIZE];

void *mymalloc(size_t size, char *file, int line){
	//printf("mymalloc\n");	
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
	if(*((char *)memory) == 0) {
		//printf("size: %d\n", (int) size);
		//assign p to point to memory[2]
		p = (void *) (memory + 9);
		
		//use first 7 bytes of each chunk as "metadata"
		//first byte is whether or not the chunk is occupied or not (0 or 1)
		//next 3 bytes are a pointer to the previous chunk (0 if there is no previous chunk)
		//next 3 bytes is the size of the chunk 
		//first byte used to determine if chunk is occupied or not
		*(memory) = 1;
		*((int *)(memory + 1)) = 0;
		*((int *)(memory + 5)) = size;	
		//initialize chunk after as unoccupied
		//and payload size of MEMSIZE - (size + 8)
		*(memory + size + 9) = 0;
		*((int *)(memory + size + 10)) = size;
		*((int *)(memory + size + 14)) = MEMSIZE - (size + 18);
		
		//the memory can support a maximum of 819 chunks concurrently
	}
	
	else {
		//check whether we have reached the end of the memory or not
		i = 0;
		//get next free chunk in memory
		int prev_chunk_size = 0;
		while(i < (MEMSIZE - 1)) {
			//printf("current value of i: %d\n", i);
			//add num of bytes to i equal to memory[i] which is the size of the current chunk
			//printf("size: %d\n", *((int *)(memory + i + 5)));
			if(*((char *)(memory + i)) == 0 && *((int *)(memory + i + 5)) >= size){
				break;
			}
			else{
				chunk_val++;
				//increment i by the size of chunk and metadata
				prev_chunk_size = *((int *)(memory + i + 5));
				i = i + *((int *)(memory + i + 5)) + 9;
			}	
		}

		//assign p with the address of the start of the chunk being assigned
		//if there are less than 5 bytes left in memory can't make a new chunk since 
		
		//printf("last value of i: %d\n", i);
		//printf("current value of *((int *)(memory + i)): %d\n", *((char *)(memory + i)));
		//printf("current value of *((int *)(memory + i + 1)): %d\n", *((int *)(memory + i + 1)));
		//printf("current value of *((int *)(memory + i + 5)): %d\n", *((int *)(memory + i + 5)));
		

		if(*((int *)(memory + i + 5)) == size){
			//there is a chunk that has perfect size
			p = (void*) (memory + i + 9);
			*(memory + i) = 1;
			*((int *)(memory + i + 1)) = prev_chunk_size;
			*((int *)(memory + i + 5)) = size;
		}

		//printf("(*((int *)(memory + i + 5)) - size): %ld\n", (*((int *)(memory + i + 5)) - size));
		else if((*((int *)(memory + i + 5)) - size) < 10){
			printf("last value of i: %d\n", i);
			printf("malloc: not enough space to create a free blocks of memory (%s:%d)\n", file, line); 
			p = (void*)0;
		}
		//ow there is enough space to create a new
		else{
			//printf("prev_chunk_size: %d\n", prev_chunk_size);
			
			//return pointer to payload of the chunk 
			p = (void*) (memory + i + 9);
			
			//set chunk to occupied with size = size
			*(memory + i) = 1;
			*((int *)(memory + i + 1)) = prev_chunk_size;
			*((int *)(memory + i + 5)) = size;
			printf("size of first chunk: %d\n", *((int *)(memory + i + 5)));
			
			//set next chunk to unoccupied with size = MEMSIZE - (i + 4)
			i = i + size + 9;
			//printf("current value of i: %d\n", i);
			*(memory + i) = 0;
			*((int *)(memory + i + 1)) = size;
			*((int *)(memory + i + 5)) = MEMSIZE - (i + 9);
			printf("size of second chunk: %d\n", *((int *)(memory + i + 5)));
			//printf("MEMSIZE - (i + 7): %d\n", MEMSIZE - (i + 9));
		}	
	}
	return p;
}

void myfree(void* ptr, char *file, int line){
	//check if pointer is within the bounds of the addresses of the memory array 
	//this will mean the pointer is from malloc ow it is not
	//printf("Beginning of memory: %p\n", memory);
	//printf("End of memory: %p\n", memory + MEMSIZE);
	//printf("char* version: %p\n", (char*)ptr);
	//printf("int* version: %p\n", (int*)ptr);
	//printf("value of i: %ld\n", (((char *)ptr) - memory));
	
	//printf("(memory + 9): %p\n", (memory + 9));
	//printf("(memory + MEMSIZE): %p\n", (memory + MEMSIZE));
	
	if((char*)ptr >= (memory + 9) && (char*)ptr < (memory + MEMSIZE)){
		//check if address is pointing to an active chunk
		//error: double free
		//printf("value ptr is pointing to: %d\n", *((char*)(ptr-9)));
		//printf("value of ptr - 4: %d\n", *((int *)(ptr - 4)));
		//printf("value of ptr - 8: %d\n", *((int *)(ptr - 8)));
		char * c = memory;
		int i = 0;
		char tf = 1;
		

		while(i < (MEMSIZE - 8)) {
                        //printf("i value: %d\n", i); 
			//printf("(char *)ptr: %p\n", (char *)ptr);
			//printf("(memory + i + 9): %p\n", (memory + i + 9));
			//printf("*((int *)(memory + i + 5)): %d\n", *((int *)(memory + i + 5)));
			if(((char *)ptr) == (memory + i + 9)){
				printf("hello world!\n");
                                tf = 0;
				break;
                        }
                        else{
                                i = i + *((int *)(memory + i + 5)) + 9;
                        }
                }


		//iterate through LL of chunks and check if any of the pointers are equivalent to the one passed 
			

		if(tf ==  1){
			printf("free: attempt to free pointer not pointing to start of chunk (%s:%d)\n", file, line);
		}


		//check if pointer is not the beginning of a chunk
		//we initialize the payload of the first chunk as 2 
		//so the value of a pointer to the beginnign of any chunk should be >= 2
		else if(*((char *)(ptr - 9)) == 0){
                	printf("free: attempt to free already freed chunk (%s:%d)\n", file,line);
                }


		else{
			int i;
			//printf("valid pointer\n");
			int size = *((int *)(ptr - 4));
			int prev_size = *((int *)(ptr - 8));

			//set this chunk as unoccupied
                	*((char*)(ptr - 9)) = 0;

                	//do memory coalescing
			//check if there is a unoccupied chunk before and a unoccupied chunk after
			if((prev_size != 0 && *((char*)(ptr - (prev_size + 18)))) && ((*((int*)(ptr + size)) == 0))) {
				printf("coalesce with chunk before and after\n");
				//remove the block after
				size = size  + *((int *)(ptr + size + 4));
				*((int *)(ptr + size + 4)) = 0;
				*((int *)(ptr + size + 1)) = 0;
				//remove the block before
				size = size + *((int *)(ptr - (prev_size + 10)));
				*((int *)(ptr - 3)) = 0;
				*((int *)(ptr - 6)) = 0;

				*((int *)(ptr - (prev_size + 3))) = size;
				
			}
			//check if there is a unoccupied chunk after
			else if((*((int*)(ptr + size)) == 0)){
				printf("coalesce with chunk after\n");
				*((int *)(ptr - 4)) = *((int *)(ptr + size + 4)) + size;
				*((int *)(ptr + size + 5)) = 0;
				*((int *)(ptr + size + 1)) = 0;
			}
			//check if there is a unoccupied chunk before
			else if(prev_size != 0 && *((char*)(ptr - (prev_size + 18))) == 0){
				printf("coalesce with chunk before\n");
				*((int *)(ptr - (prev_size + 13))) = *((int *)(ptr - (prev_size + 13))) + size + 9;
				printf("new size: %d\n", *((int *)(ptr - (prev_size + 13))));
				*((int *)(ptr - 4)) = 0;
				*((int *)(ptr - 8)) = 0;
				if((char *)(ptr + size) < (memory + MEMSIZE)){
					*((int *)(ptr + size + 5)) = *((int *)(ptr - (prev_size + 13)));
				}
			}

			//printf("value ptr is pointing to: %d\n", *((char*)(ptr-9)));
                	//printf("value of ptr - 4: %d\n", *((int *)(ptr - 4)));
                	//printf("value of ptr - 8: %d\n", *((int *)(ptr - 8)));	
		}
		
	}
	//error: attempt to free non-block ptr
	else{
		//printf("pointer value: %p\n", (char*)ptr);
		//printf("Beginning of memory: %p\n", (memory + 2));
        	//printf("End of memory: %p\n", (memory + MEMSIZE));
		printf("free: attempt to free non-block ptr (%s:%d)\n", file, line);
	}	
}
