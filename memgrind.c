#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mymalloc.h"
/**
 * Performance testing
 *
 * The program should perform the following
 * tasks:
 * 1. malloc() and immediately free() a 1-byte chunk, 120 times.
 * 2. Use malloc() to get 120 1-byte chunks, storing the pointers in an array, then use free() to
 * deallocate the chunks.
 * 3. Randomly choose between
 * Allocating a 1-byte chunk and storing the pointer in an array
 * Deallocating one of the chunks in the array (if any)
 * Repeat until you have called malloc() 120 times, then free all remaining allocated chunks.
 * 4. Two more stress tests of your design. Document these in your README.
 *
 */

int main() {
	srand(time(NULL));
	//task 1
	int i;
	void * p;
	int r;
	int num_pointers;
	//last added pointer to the list
	int counter;
	for (i = 0; i < 120; i++) {
		p = malloc(1);
		free(p);
	}
	
	//task 2
	num_pointers = 120;
	void * pointers[num_pointers];
	for (i = 0; i < num_pointers; i++) {
		p = malloc(1);
		pointers[i] = p;
	}

	for (i = 0; i < num_pointers; i++) {
		free(pointers[i]);
	}
	
	//task 3
	counter = 0;
	for (i = 0; i < num_pointers; i++) {
		//random binary 0 or 1
		r = rand() % 2;
		if(r == 0){
			p = malloc(1);
			pointers[counter] = p;
			counter++;	
		}
		else{
			free(pointers[counter]);
			counter--;
		}
	}

	//task 4: design a performance test
	

	//task 5: design a performance test
	
	//run each task 50 times counting number of seconds it takes to run each task
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 50; j++) {
			if(i == 0) {
				task1();
			}
			else if(i == 1) {
				task2();
			}
			else {
				task3();
			}
			
		}
	}
	return 0;
}
