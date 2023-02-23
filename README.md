# CS214 Proj 1

GROUP MEMBERS: Kevin Su (ks1507)
               Ghautham Sambabu (gs878)

# Test Plan
(a) The properties that our library needs to have in order for it to be correct is:
        
1. A call to malloc should find the next available chunk that is big enough to accomodate the number of bytes requested and return a pointer to the payload of that chunk
	- if the chunk is big enough to split we will create one chunk with size
	- ow return the entire chunk 

2. A call to malloc should detect if there's enough space in the memory array to accomodate the number of bytes requested if not it should return an error message: "malloc: not enough space to create a free blocks of memory (%s:%d)\n", file, line
        
3. A call to free should check if the ptr passed to it is a pointer to a chunk in the static memory array if not it should print the following error message: "free: attempt to free non-block ptr (%s:%d)\n", file, line
	
4. A call to free should check if the ptr passed to it is pointing to the beginning of a chunk if not it should print the following error message: "free: attempt to free pointer not pointing to start of chunk (%s:%d)\n", file, line
	
5. A call to free should check if chunk passed to it is occupied or not, ow it should print the following error message: "free: attempt to free already freed chunk (%s:%d)\n", file,line

6. After checking if the pointer is valid or not a call to free should mark the chunk as unoccupied and check for coalescing
    
(b) We intend to check these 6 properties listed by creating additional test files: test.c and tset2.c which will go over each of the cases described above. We will use various methods to evaluate how the methods(malloc and free) and the array interact with each other. More specifically, in our mymalloc.c source code we use conditional compilation by checking for the definition of a test macro. When we link our test.c file and mymalloc.c we include this macro providing us additional print and debugging statements for the sake of our correctness testing. We additionally make use of the basic test cases provided to us in err.c and used that to provide a base line level of correctness testing for our code. The first test file (test.c) will take a look at the basic cases as well as some edge case like call malloc twice or allocating memory which is too large for the global array. The second test file (test2.c) places a special emphasis on how well does the free method coalesce the free chuncks of memory. 
    
(c)Correctness tests
	
Test.c
---
Test 1: Free the memory at an address that isn't returned by malloc()

Test 2: Free the same address a second time

Test 3: Free memory that isnt already allocated  by malloc()
	
Test 4: Allocate memory that is larger than the global array

Test 5: Run a valid test to see if our malloc() and free() works

Test2.c
---
Test 6: check if free() coalesces previous chunks

Test 7: check if free() coalesces future chunks
	
Test 8: check if free() coalesces previous and future chunks
	
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

To run correctness tests:
```
./err 1
./err 2
./err 3

./test 1
./test 2
./test 3
./test 4

./test2 1
./test2 2
./test2 3
./test2 4
```

# Proof of design properties functioning properly

err.c
- case 1: successfully gives us an error message
- case 2: successfully gives us an error message
- case 3: successfully gives us an error message

test.c



# Additional design notes
- Our meta data is 9 bytes
	- the first byte indicates whether or not the chunk is being occupied 
	- the next four bytes indicate the size of the previous chunk
	- the next four bytes indicate the size of the chunk
- We use eager coalescing
	- every time free is called we check to see if there are any adjacent free blocks to the current chunk and if so we coalesce them.
- Similar to real malloc() if mymalloc() is passed 0 as an argument it returns a NULL pointer.
- If malloc() finds a chunk that can accomodate the number of bytes requested but cannot meaningfully split the chunk into another chunk it will return the pointer to the payload of that chunk.
