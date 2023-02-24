#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "mymalloc.h"

//check edge cases of number of bytes able to be allocated
void test1(){
	void * p;
	//biggest chunk that can be
    	printf("-- malloc(4087) --\n");
	p = malloc(4087);
	if(p){
		printf("SUCCESS! returned a valid pointer\n");
	}
	else{
		printf("FAILURE! returned a NULL pointer\n");
	}
	//should print error
	malloc(1);
	free(p);
	printf("-- malloc(4088) --\n");
	p = malloc(4088);
	if(!p){
		printf("SUCCESS! returned a NULLl pointer\n");
	}
	else{
		printf("FAILURE! didn't return a NULL pointer\n");
	}
	printf("-- malloc(4086) to malloc(4077) --\n");
	for(int i = 4086; i >= 4077; i--){
		p = malloc(i);
		free(p);
	}
	p = malloc(4076);
	free(p);
	p = malloc(4075);
	free(p);
	
}

//check if malloc(0) returns a NULL pointer
void test2(){
	void * p = malloc(0);
	if(!p){
		printf("SUCCESS! returned a NULL pointer\n");
	}
	else{
		printf("FAILURE! didn't return a NULL pointer\n");
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
	//should print coalesce with chunk before 6 times and coalesce with chunk after 1 time
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

//simple check for coalesce with chunk after
void test5(){
	void * p1 = malloc(1);
	void * p2 = malloc(4077);
	free(p1);
	free(p2);
}

//simple check for coalesce with chunk before
void test6(){
	void * p1 = malloc(1);
	void * p2 = malloc(4077);
	free(p2);
	free(p1);
}


//simple check for coalesce with chunk before and chunk after
void test7(){
	void * p1 = malloc(1356);
	void * p2 = malloc(1356);
	void * p3 = malloc(1356);
	free(p1);
	free(p3);
	free(p2);
}


int main(int argc, char **argv) {
	int test = argc > 1 ? atoi(argv[1]) : 0;

        switch (test) {
                default:
                        puts("Missing or invalid test number");
                        return EXIT_FAILURE;

                case 1:
                        printf("-- test1 --\n");
        		test1();
                        break;
                case 2:
                        printf("-- test2 --\n");
        		test2();
                        break;

                case 3:
                        printf("-- test3 --\n");
        		test3();
                        break;

		case 4: 
			printf("-- test4 --\n");
        		test4();
			break;
        	case 5: 
			printf("-- test5 --\n");
			test5();
			break;
		case 6:
			printf("-- test6 --\n");
			test6();
			break;
		case 7:
			printf("-- test7 --\n");
			test7();
			break;
	
	}	
	return 0;
}
