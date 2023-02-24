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
	
