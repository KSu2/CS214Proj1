#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
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

void task1() {
	//task 1
        int i;
        void * p;
        for (i = 0; i < 120; i++) {
                p = malloc(1);
                free(p);
        }
}

void task2() {
	int i;
	int num_pointers = 120;
        void * pointers[num_pointers];
	void * p;
        for (i = 0; i < num_pointers; i++) {
                p = malloc(1);
                pointers[i] = p;
        }

        for (i = 0; i < num_pointers; i++) {
		free(pointers[i]);
        }
}

void task3() {
	srand(time(NULL));
	//index of last pointer from malloc()
	int i = 0;
	//counter of times malloc() was called
	int counter = 0;
	//current count of pointers
	int curr_pointers = 0;
	int num_pointers = 120;
	
	void * p;
	double r;
	void * pointers[num_pointers];
        
	while (counter < 120) {
                //random binary 0 or 1 
		r = rand() % 2;
		
		if(r == 0){
                	counter++;
			curr_pointers++;
			if(counter != 1){
				i++;
			}
			p = malloc(1);
                        pointers[i] = p;
                }
		//if r == 1 and there is a valid chunk free it
		else if(curr_pointers > 0){
		        free(pointers[i]);
                	i--; 
			curr_pointers--;
                }
        }
	//free the rest of the pointers
	while(i > 0) {
		free(pointers[i]);
		i--;
	}	
}


// spliting the 4096 byte array into random nuber of chunks using malloc by powers of 2 then freie 
void task4() {
	srand(time(NULL));
	int i;
	int num_pointers = 4096/(pow(2,1+(rand() % 12)));
    	printf("num_pointers: %d\n", num_pointers);
	void * pointers[num_pointers];
	void * p;
        for (i = 0; i < num_pointers; i++) {
                p = malloc(1);
                pointers[i] = p;
        }

        for (i = 0; i < num_pointers; i++) {
                free(pointers[i]);
        }


}

//random stress test then free them in reverse
void task5() {
	srand(time(NULL));
	int i;
	int num_pointers = 1+(rand() % 128);
	printf("num_pointers: %d\n", num_pointers);
    	void * pointers[num_pointers];
	void * p;
        for (i = 0; i < num_pointers; i++) {
                p = malloc(1);
                pointers[i] = p;
        }

        for (i = num_pointers-1; i >= 0; i--) {
                free(pointers[i]);
        }	
}



int main() {
	int i, j;
	clock_t t;
	double time_taken;
		
	//run each task 50 times counting number of seconds it takes to run each task
	for (i = 0; i < 5; i++) {
		time_taken = 0;
		for (j = 0; j < 50; j++) {
			t = clock();
			if(i == 0) {
				task1();
			}
			else if(i == 1) {
				task2();
			}
			else if(i == 2){
				task3();
			}
			else if(i == 3){
				task4();
			}
			else if(i == 4){
				task5();
			}

			t = clock() - t;	
			time_taken += ((double)t)/CLOCKS_PER_SEC;
		}
		printf("--- task: %d took an average of %f seconds to execute ---\n",(i+1),(time_taken/50));
	}
	return 0;
}
