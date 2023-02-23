#include <stdio.h>
#include "mymalloc.h"

//completely fill up the memory array
void test1(){
	void * p;
	//biggest chunk that can be
    	p = malloc(4087);
	if(p){
		printf("SUCCESS! returned a valid pointer\n");
	}
	else{
		printf("FAILURE! returned a NULL pointer\n");
	}
	p = malloc(1);
	free(p);
	p = malloc(4088);
	if(!p){
		printf("returned a NULLl pointer\n");
	}
	else{
		pritnf("didn't return a NULL pointer\n");
	}
	free(p);
	p = malloc(4086);
	free(p);
	p = malloc(4085);
	free(p);
	p = malloc(4084);
	free(p);
}

//check if malloc(0) returns a NULL pointer
void test2(){
	void * p = malloc(0);
	if(!p){
		printf("SUCESS! returned a NULL pointer\n");
	}
	else{
		printf("FAIL! didn't return a NULL pointer\n");
	}
}

//check for forward and backwards coalescing
void test3(){
	int i;
	void * p;
	void * pointers[8];
	for(i = 0; i < 8; i++){
		p = malloc(455);
		pointers[i] = p;
	}

	//coalesce with chunks before
	for(i = 0; i < 8; i++){
		free(pointers[i]);
	}
}

void test4(){
        int i;
        void * p;
        void * pointers[8];
        for(i = 0; i < 8; i++){
                p = malloc(455);
                pointers[i] = p;
        }
	
        //coalesce with chunks after
        for(i = 7; i >= 0; i--){
                free(pointers[i]);
        }
}


int main() {
	printf("-- test1 --\n");
	test1();
	printf("-- test2 --\n");
	test2();
	printf("-- test3 --\n");
	test3();
	printf("-- test4 --\n");
	test4();
	return 0;
}
