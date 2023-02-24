#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "mymalloc.h"
#define MEMSIZE 4096

static char memory[MEMSIZE];

void *mymalloc(size_t size, char *file, int line){
	//9 bytes for "metadata"	
	//create void pointer p	
	void *p;
	
	//counting variables
	int i;
	
	//edge case: malloc(0)
	if(size == 0) {
		//return null pointer
		return (void*)0;
	}
	
	//memory is uninitialized
	else if(*((char *)memory) == 0 && *((int *)(memory + 5)) == 0) {
		//if array is uninitialized the size of the payload is MEMSIZE - 9
		if((MEMSIZE - 9) < size){
                        printf("malloc: not enough space to allocate specified number of bytes (%s:%d)\n", file, line);
                        p = (void*)0;
                }
		else if((MEMSIZE - 9) < size + 10){
			#ifdef test
			printf("fill entire memory\n");
			#endif
			p = (void *) (memory + 9);
			*(memory) = 1;
			*((int *)(memory + 1)) = 0;
			*((int *)(memory + 5)) = MEMSIZE - 9;
		}
		else{
			p = (void *) (memory + 9);
		
			//use first 9 bytes of each chunk as "metadata"
			//first byte is whether or not the chunk is occupied or not (0 or 1)
			//next 4 bytes is the size of the previous chunk (0 if there is no previous chunk)
			//next 4 bytes is the size of the current chunk 
			//first byte used to determine if chunk is occupied or not
			*(memory) = 1;
			*((int *)(memory + 1)) = 0;
			*((int *)(memory + 5)) = size;	
			//initialize chunk after as unoccupied
			//and payload size of MEMSIZE - (size + 8)
			*(memory + size + 9) = 0;
			*((int *)(memory + size + 10)) = size;
			*((int *)(memory + size + 14)) = MEMSIZE - (size + 18);
		
		}
	}
	
	else {
		//check whether we have reached the end of the memory or not
		i = 0;
		//get next free chunk in memory
		int prev_chunk_size = 0;
		while(i < (MEMSIZE)) {
			if(*((char *)(memory + i)) == 0 && *((int *)(memory + i + 5)) >= size){
				break;
			}
			else{
				//increment i by the size of chunk and metadata
				prev_chunk_size = *((int *)(memory + i + 5));
				i = i + *((int *)(memory + i + 5)) + 9;
			}	
		}

		
		
		if((*((int *)(memory + i + 5))) < size){
			printf("malloc: not enough space to allocate specified number of bytes (%s:%d)\n", file, line); 
			p = (void*)0;
		}
		
		//enough space for the chunk but not enough room to split into another chunk
		//since "metadata" is 9 bytes chunk_size needs to be > size + 10 bytes to meaningfully split
		else if(*((int *)(memory + i + 5)) < (size + 10)){
			#ifdef test
			printf("assign entire chunk\n");
			#endif
			p = (void *)(memory + i + 9);
                        *(memory + i) = 1;
                        *((int *)(memory + i + 1)) = prev_chunk_size;
                }
		//There is enough space to split into two chunks
		else{
			//return pointer to payload of the chunk 
			p = (void*) (memory + i + 9);
			
			//set chunk to occupied with size = size
			*(memory + i) = 1;
			*((int *)(memory + i + 1)) = prev_chunk_size;
			*((int *)(memory + i + 5)) = size;
			
			
			//set next chunk to unoccupied with size = MEMSIZE - (i + 9)
			i = i + size + 9;
			
			*(memory + i) = 0;
			*((int *)(memory + i + 1)) = size;
			*((int *)(memory + i + 5)) = MEMSIZE - (i + 9);
			
		}	
	}
	return p;
}

void myfree(void* ptr, char *file, int line){
	if((char*)ptr >= (memory + 9) && (char*)ptr < (memory + MEMSIZE)){
		//check if address is pointing to an active chunk
		//error: double free
		//printf("value ptr is pointing to: %d\n", *((char*)(ptr-9)));
		//printf("value of ptr - 4: %d\n", *((int *)(ptr - 4)));
		//printf("value of ptr - 8: %d\n", *((int *)(ptr - 8)));
		char * c = memory;
		int i = 0;
		char is_beginning = 1;
		

		while(i < (MEMSIZE)) {
                        if(((char *)ptr) == (memory + i + 9)){
				is_beginning = 0;
				break;
                        }
                        else{
                                i = i + *((int *)(memory + i + 5)) + 9;
                        }
                }

		//iterate through LL of chunks and check if any of the pointers are equivalent to the one passed 
			

		if(is_beginning ==  1){
			printf("free: attempt to free pointer not pointing to start of chunk (%s:%d)\n", file, line);
		}


		//check if pointer is not the beginning of a chunk
		//we initialize the payload of the first chunk as 2 
		//so the value of a pointer to the beginnign of any chunk should be >= 2
		else if(*((char *)(ptr - 9)) == 0){
                	printf("free: attempt to free already freed chunk (%s:%d)\n", file,line);
                }


		else{
			int size = *((int *)(ptr - 4));
			int prev_size = *((int *)(ptr - 8));
			//pointer to payload of chunk before
			void * chunk_before = ptr - (prev_size + 9);
			//pointer to payload of chunk after
			void * chunk_after = ptr + (size + 9);
			
			//set this chunk as unoccupied
                	*((char*)(ptr - 9)) = 0;

                	//do memory coalescing
			//check if there is a unoccupied chunk before and a unoccupied chunk after
			if((prev_size != 0 && *((char *)(chunk_before - 9)) == 0) && (((char *)chunk_after < (memory + (MEMSIZE - 9))) && (*((char *)(chunk_after - 9)) == 0))) {
				#ifdef test
                                printf("coalesce with chunk before and after\n");
                                #endif
				//remove the block after
				size = size  + *((int *)(chunk_after - 4));
				*((int *)(chunk_after - 4)) = 0;
				*((int *)(chunk_after - 8)) = 0;
				//remove the block before
				size = size + *((int *)(chunk_before - 4));
				*((int *)(ptr - 4)) = 0;
				*((int *)(ptr - 8)) = 0;

				*((int *)(chunk_before - 4)) = size + 18;
				
			}
			//check if there is a unoccupied chunk after
			else if((char *)(chunk_after) < (memory + MEMSIZE) && *((char *)(chunk_after - 9)) == 0){
				#ifdef test
				printf("coalesce with chunk after\n");
				#endif
				
				*((int *)(ptr - 4)) = *((int *)(chunk_after - 4)) + size + 9;
				*((int *)(chunk_after - 4)) = 0;
				*((int *)(chunk_after - 8)) = 0;
			}
			//check if there is a unoccupied chunk before
			else if(prev_size != 0 && *((char*)(ptr - (prev_size + 18))) == 0){
				#ifdef test
                                printf("coalesce with chunk before\n");
                                #endif
				
				*((int *)(ptr - (prev_size + 13))) = *((int *)(ptr - (prev_size + 13))) + size + 9;
				*((int *)(ptr - 4)) = 0;
				*((int *)(ptr - 8)) = 0;
				if((char *)(ptr + size) < (memory + (MEMSIZE - 10))){
					*((int *)(ptr + size + 1)) = *((int *)(ptr - (prev_size + 13)));
				}
			}
	
		}
		
	}
	//error: attempt to free non-block ptr
	else{
		printf("free: attempt to free non-block ptr (%s:%d)\n", file, line);
	}	
}
