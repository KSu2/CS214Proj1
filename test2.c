#include <stdio.h>
#include "mymalloc.h"

int main() {
	char arr[4];
	size_t size = 1000 * sizeof(int);
	
	int i;
	void * p;
	void *pointers[120];
	for(i = 0; i < 5; i++){
		p = malloc(1);
		pointers[i] = p;
	}
	for(i = 0; i < 5; i++){
		free(pointers[i]);
	}
	
	return 0;
}
