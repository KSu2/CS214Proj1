# CS214 Proj 1

GROUP MEMBERS: Kevin Su (ks1507),
               Ghautham Sambabu (gs878)

# Test Plan
(a) The properties that our library needs to have in order for it to be correct is:
        
1. A call to malloc should find the first available chunk with a payload size that is big enough to accomodate the number of bytes requested and return a pointer to the payload of that chunk:
	- If the chunk payload is big enough to split we will create one chunk with size requested and another with size (original_size - (size + meta_data_size)).
	- Otherwise, we won't split and just assign the entire chunk as occupied. 

2. A call to malloc should detect if there's enough space in the memory array to accomodate the number of bytes requested if not it should return an error message: "malloc: not enough space to create a free blocks of memory (%s:%d)\n", file, line.
        
3. A call to free should check if the ptr passed to it is a pointer to a chunk in the static memory array if not it should print the following error message: "free: attempt to free non-block ptr (%s:%d)\n", file, line.
	
4. A call to free should check if the ptr passed to it is pointing to the beginning of a chunk if not it should print the following error message: "free: attempt to free pointer not pointing to start of chunk (%s:%d)\n", file, line.
	
5. A call to free should check if chunk passed to it is occupied or not, ow it should print the following error message: "free: attempt to free already freed chunk (%s:%d)\n", file,line.

6. After checking if the pointer is valid or not a call to free should mark the chunk as unoccupied and check for coalescing.

7. Our mymalloc() and myfree() should not try to access addresses outside of the memory array as this will lead to unintended behaviours.
    
(b) We intend to check these 6 properties listed by creating additional test files: test.c and tset2.c which will go over each of the cases described above. We will use various methods to evaluate how the methods(malloc and free) and the array interact with each other. More specifically, in our mymalloc.c source code we use conditional compilation by checking for the definition of a test macro. When we link our test.c file and mymalloc.c we include this macro providing us additional print and debugging statements for the sake of our correctness testing. We additionally make use of the basic test cases provided to us in err.c and used that to provide a base line level of correctness testing for our code. The first test file (test.c) will take a look at the basic cases as well as some edge case like call malloc twice or allocating memory which is too large for the global array. The second test file (test2.c) places a special emphasis on how well does the free method coalesce the free chuncks of memory. 
    
(c)Correctness tests
	
Test.c
---
Test1(): Check the basic functionality of malloc() and free(). Call malloc(200) then free(), then call malloc(200) and free() again. Then compare the first and second pointer from malloc. They should be the same as the expected behavior is for our program to free() the first chunk and coalesce and then the second call to malloc() should give us the same pointer. This test is to check properties 3-6 of our design.

Test2(): Check if malloc() catches error of not having enough memory when memory is uninitialized. Call malloc(5000) and cheeck if the pointer is a NULL pointer. The expected result is for malloc() to return a NULL pointer as 5000 is greater than MEMSIZE which is 4096. This shows property 2 of our design.

test3(): Check if malloc() catches error of not having enough memory when memory is initialized. Call mallor(4087) which will mark the entirity of the memory array as occupied. Then call malloc(1) to check if malloc() will return a NULL pointer and print the appropriate error message. This test is to check property 1 and 7 of our design.

Test2.c
---
Test1(): Check the edge cases of malloc sizes 4087, 4088, 4086, 4085, 4084. The expected result is that for malloc(4088) we should receive an error message and be returned a NULL pointer since the biggest number of bytes that can be allocated is 4097 - 9 = 4087 due to our design using 9 bytes for metadata. For any number of bytes from 4087 - 4077, malloc() should assign the whole payload to occupied and not be able to split. This test shows properties 1 & 2 of our design

Test2(): Check if malloc(0) returns a NULL pointer. This checks our design decision to have malloc(0) return a NULL pointer instead of wasting memory by creating a new metadata header. 

Test3(): Call malloc(455) 8 times. The result of this should be check if free() coalesces previous chunks

Test4(): check if free() coalesces future chunks
	
Test5(): Check if a simple example of coalescing with the chunk after works properly.

Test6(): Check if a simple example of coalescing with the chunk after works properly.

Test7(): Check if a simple example of coalescing with the chunks before and after works properly.

err.c
---
case 1: check if myfree() prints an error when passed a non-block pointer (property 3) 

case 2: check if myfree() prints an error when passed a ptr that isn't at the start of a chunk (property 4)

case 3: check if myfree() prints an error when passed a ptr to a chunk that has already been freed (property 5)
    
(d) Performace tests(outside of the ones assigned)

Task4(): 
We split the 4096 byte array into random number of chunks which are determined by powers of 2 (1-12) 
then free the chunk(s)  

Task5(): 
We randomly choose the number of pointers to then use that number to divide the total number of bytes of the 4096 bytes
available then free the memory in reverse

# How to run code

First need to build executable files:
```
make test
make test2
make err
make memgrind
```
To run performance tests:
```
./memgrind
```

To run correctness tests (./[test-executable] [test-number]) :

err case1: 
```
./err 1
```
err case2:
```
./err 2
```
err case3:
```
./err 3
```

test.c test1():
```
./test 1
```
test.c test2():
```
./test 2
```
test.c test4():
```
./test 3
```

test2.c test1():
```
./test2 1
```
test2.c test2():
```
./test2 2
```
test2.c test3():
```
./test2 3
```
test2.c test4():
```
./test2 4
```
test2.c test5():
```
./test2 5
```
test2.c test6():
```
./test2 6
```
test2.c test7():
```
./test2 7
```

# Proof of design properties functioning properly

err.c
- case 1: successfully gives us an error message, free: attempt to free non-block ptr (err.c:16)
- case 2: successfully gives us an error message, free: attempt to free pointer not pointing to start of chunk (err.c:20)
- case 3: successfully gives us an error message, free: attempt to free already freed chunk (err.c:26)

test.c
- test 1:  
- test 2: 
- 

# Additional design notes
- Our meta data is 9 bytes
	- the first byte indicates whether or not the chunk is being occupied 
	- the next four bytes indicate the size of the previous chunk
	- the next four bytes indicate the size of the chunk
- We use eager coalescing, every time free() is called we check to see if there are any adjacent free blocks to the current chunk and if so we coalesce them.
- Similar to real malloc() if mymalloc() is passed 0 as an argument it returns a NULL pointer.
- If malloc() finds a chunk that can accomodate the number of bytes requested but cannot meaningfully split the chunk into another chunk it will return the pointer to the payload of that chunk.
