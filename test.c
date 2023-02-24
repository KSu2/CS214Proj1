#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "mymalloc.h"



// Check free
void test1(){
    void * org = malloc(200);
    free(org);
    int * copy = org;
    org = malloc(200);
    free(org);
    if(org==copy){
        printf("SUCCESS! x = z = %p. New malloced address is the same as the old one.\n",copy);
    }
    else{
    	printf("FAILURE! Invalid Free().\n");
    }
}

//check allocating more than 4069 bytes
void test2(){
    	void * t = malloc(5000);
    	if(!t){
    		printf("SUCCESS! returned a NULL pointer and didn't allocate 5000 bytes\n");
    	}
    	else{
    		printf("FAILURE! didn't return a NULL pointer and allocated more bytes than exist in memory\n");
    	}
	free(t);
}

void test3(){
	void * p1 = malloc(4087);
	//should print error message and return a null pointer
	void * p2 = malloc(1);
	if(!p2){
		printf("SUCCESS! didn't allocate more than 4096 bytes\n");
	}
	else{
		printf("FAILURE! didn't return a NULL pointer, therefore allocated more than 4986 bytes\n");
	}
}

void test4(){
	void * p1 = malloc(100);
	void * p2 = malloc(100);
	void * p3 = malloc(100);

	free(p2);
	p2 = malloc(50);
	free(p2);
	if(p2){
		printf("SUCCESS! allocated memory chunk between two other occupied chunks\n");
	}
	else{
		printf("FAILURE! unable to allocate chunk\n"); 
	}
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
	return 0;
}
