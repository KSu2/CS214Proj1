#include <stdio.h>
#include "mymalloc.h"

int main() {
	void* p = malloc(sizeof(int));
	

	
	free(p);
	int a = 1;
	void* p2 = &a;
	free(p2);

	return 0;
}
