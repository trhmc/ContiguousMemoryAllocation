# ContiguousMemoryAllocation
## Initalized memory allocation
	Max array size (example ```./allocator 5```)

Process class:
- memory size
- ID of the process (example: P0)

memory_block class:
- memory size
- ID of the memory block
- array of process occupied
- pushing a process into the block
- popping the process off the block
- bool empty: checking of a block is empty or not

## 4 essential functions:
1. RQ [process] [memory size] [strategy] - request for a contiguous block of memory
	- W - worst fit, fitting largest block of memory possible to process
	- B - best fit, fitting closest size block of memory possible to process
	- F - first fit, fitting first block of memory of equal or larger size to process
2. RL [process] - release of a contiguous block of memory
3. C - compact unused holes of memory into one single block
4. STAT - report regions of free and allocated memory
5. Exit - exit the program

main:
- help menu of function

## Assumptions
Status report will only show the status base on the processes (if there's any active on the system)

## How to run program:
- Compile program
```
	g++ -o alloc Allocator.cpp
```
- Running program
```
	./alloc 3
```
(Here the program is initialized with 3 blocks of memory, user will input size of each block)
- Function examples:
```
	RQ P0 150 W
	STAT
	RL P0
	STAT
	C
	Exit
```
### reference source:
https://www.geeksforgeeks.org/implementation-of-all-partition-allocation-methods-in-memory-management/