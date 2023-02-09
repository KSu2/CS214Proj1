#include <stdio.h>
#include "mymalloc.h"

int main() {
	printf("Hello world \n");
	void* p = malloc(sizeof(int));
	printf("This is a pointer created from mymalloc() %p\n",p);
	printf("value of pointer created from mymalloc() %d\n", *((int *)p));
	printf("value of next byte from pointer created from mymalloc() %d\n", *(((int *) p) + 1));
	printf("value of next byte from pointer created from mymalloc() %d\n", *(((int *) p) + 2));
	free(p);
	int a = 1;
	void* p2 = &a;
	free(p2);

	return 0;
}
