CC=gcc

mymalloc: test.o mymalloc.o
	gcc -o mymalloc test.o mymalloc.o

test2: test2.o mymalloc.o
	gcc -o test2 test2.o mymalloc.o

memgrind: memgrind.o mymalloc.o
	gcc -o memgrind memgrind.o mymalloc.o -lm

err: err.o mymalloc.o
	gcc -o err err.o mymalloc.o

test.o: test.c mymalloc mymalloc.h
	gcc -c test.c

test2.o: test2.c mymalloc mymalloc.h
	gcc -c test2.c

mymalloc.o: mymalloc.c mymalloc.h
	gcc -c mymalloc.c

memgrind.o: memgrind.c mymalloc.h
	gcc -c memgrind.c

err.o: err.c mymalloc.h
	gcc -c err.c
