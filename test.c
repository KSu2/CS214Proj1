#include <stdio.h>
#include "mymalloc.h"

void test_one(){
	int testOne = 23;
	void * a = &testOne;
	free(a);
}
void test_two(){
    int * testTwo = (int*) malloc(sizeof(int)*100);
    free(testTwo+10);
}

void test_three(){
    int *testThree = (int*) malloc(100);
    free(testThree);
    free(testThree);
}

// Valid free
void test_four(){
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

void test_five(){
    int *t = (int*) malloc(5000);
}
int main() {
	void* p = malloc(sizeof(int));
	
	free(p);
	int a = 1;
	void* p2 = &a;
	free(p2);
	// Performace tests
	//Free mem that isnt malloc()
	test_one();
	
	//Free the mem at an address that isnt returned by malloc()
	test_two();
	
	//Free the same address a second time
	test_three();
		
	//Run a valid test to see if our malloc() and free() works
	test_four();

	//Too much mem
	test_five();

	return 0;
}
