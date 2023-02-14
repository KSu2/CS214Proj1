CC=gcc

mymalloc: test.o mymalloc.o
	gcc -o mymalloc test.o mymalloc.o

memgrind: memgrind.o mymalloc.o
	gcc -o memgrind memgrind.o mymalloc.o

err: err.o mymalloc.o
	gcc -o err err.o mymalloc.o

test.o: test.c
	gcc -c test.c

mymalloc.o: mymalloc.c mymalloc.h
	gcc -c mymalloc.c

memgrind.o: memgrind.c mymalloc.h
	gcc -c memgrind.c

err.o: err.c mymalloc.h
	gcc -c err.c
