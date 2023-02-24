#include <stdio.h>
#include "mymalloc.h"

void test1(){
	void * p1 = malloc(200);
	free(p1);
	void * p2 = malloc(200);
	if(p1 == p2){
		printf("SUCCESS! pointer is successfully created and freed");
	}
	else{
		printf("FAILURE! free() did not work as intended");
	}
}
//check double free
void test2(){
	void * t = malloc(5000);
	if(!t){
		printf("SUCCESS! uninitialized memory did not allocate memory when size > 4087");
	}
	else{
		printf("FAILURE! uninitialized memory allocated memory when it was not supposed to");
	}
}

void test3(){
        void * t = malloc(4087);
        void * p = malloc(1);
        if(!p){
		printf("SUCCESS! didn't allocate memory when initialized memory was full");
	}
	else{
		printf("FAILURE! allocated memory when it wasn't supposed to");
	}
}

void test4(){
	void * p1 = malloc(100);
	void * p2 = malloc(100);
	void * p3 = malloc(100);
	free(p2);
	p2 = malloc(100);
}

int main(int argc, char **argv){
        int test = argc > 1 ? atoi(argv[1]) : 0;

        switch (test) {
                default:
                        puts("Missing or invalid test number");
                        return EXIT_FAILURE;
                case 1:
                        test1();
                        break;
                case 2:
                        test2();
                        break;
                case 3:
                        test3();
                        break;
                case 4:
                        test4();
                        break;
	}
}
