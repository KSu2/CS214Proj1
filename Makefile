CC=gcc

test: test.o mymalloctest.o
	gcc -fsanitize=address -o test test.o mymalloctest.o

test2: test2.o mymalloctest.o
	gcc -fsanitize=address -o test2 test2.o mymalloctest.o

memgrind: memgrind.o mymalloc.o
	gcc -fsanitize=address -o memgrind memgrind.o mymalloc.o -lm

err: err.o mymalloc.o
	gcc -fsanitize=address -o err err.o mymalloc.o

test.o: test.c mymalloc.c mymalloc.h
	gcc -c test.c

test2.o: test2.c mymalloc.c mymalloc.h
	gcc -c test2.c

mymalloctest.o: mymalloc.c mymalloc.h
	gcc -Dtest -o mymalloctest.o -c mymalloc.c

mymalloc.o: mymalloc.c mymalloc.h
	gcc -c mymalloc.c

memgrind.o: memgrind.c mymalloc.h
	gcc -c memgrind.c

err.o: err.c mymalloc.c mymalloc.h
	gcc -c err.c
