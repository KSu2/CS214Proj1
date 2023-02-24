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


int main() {

	test_one();
	
	test_two();
	
	test_three();
		
	test_four();

	test_five();

	return 0;
}
