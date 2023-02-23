#include <stdio.h>
#include "mymalloc.h"

//check free for pointer not at beginning of chunk
void test_one(){
    int * testTwo = (int*) malloc(sizeof(int)*100);
    free(testTwo+10);
}
//check double free
void test_two(){
    int *testThree = (int*) malloc(100);
    free(testThree);
    free(testThree);
}

//check basic free case
void test_three(){
	int testOne = 23;
	void * a = &testOne;
	free(a);
}

//check allocating more than 4069 bytes
void test_four(){
    void * t = malloc(5000);
}


// Valid free
void test_five(){
    void * org = malloc(200);
    free(org);
    int * copy = org;
    org = malloc(200);
    free(org);
    if(org==copy){
        printf("x = z = %p. New malloced address is the same as the old one.\n",copy);
    }
    else{
    	printf("Perfectly Valid Free().\n");
    }
}


int main() {

	test_one();
	
	test_two();
	
	test_three();
		
	test_four();

	test_five();

	return 0;
}
