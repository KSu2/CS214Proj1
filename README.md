# CS214Proj1

GROUP MEMBERS: Kevin Su (ks1507)
               Ghautham Sambabu (gs878)

Test Plan
    (a) The properties that our library needs to have in order for it to be correct is:
        
        1. A working malloc method that save memory within the file limit
        
        2. A working free method that deallocates memory that is specified in a parameter and can't be called redudantly
        
        3. A global static array that stores/deallocates data and metadata based on the calls from malloc and free methods
    
    (b) We intend to check these properties by creating 5 tests in test.c in various methods to evaluate how the methods(malloc and free) and the array interact with each other as well as the performace tests in memegrind.c
    
    
    (c)	Correctness tests
		
        Test 1: Free memory that isnt already allocated  by malloc()

	Test 2: Free the memory at an address that isn't returned by malloc()
	
	Test 3: Free the same address a second time
	
	Test 4: Run a valid test to see if our malloc() and free() works
	
	Test 5: Allocate memory that is larger than the global array     
    
    (d) Performace tests(outside of the ones assigned)

Proof of design properties functioning properly

Additional design notes
- Our meta data is 9 bytes
	- the first byte indicates whether or not the chunk is being occupied 
	- the next four bytes indicate the size of the previous chunk
	- the next four bytes indicate the size of the chunk
- We use eager coalescing
	- every time free is called we check to see if there are any adjacent free blocks to the current chunk and if so we coalesce them
