/*
Memory management functions
(C) 2014 Konstantin Dimitrov
*/

#ifndef _MEMORY_H
#define _MEMORY_H

#define M(addr) (*(void volatile far*)(addr))				// macro definition for provision of unspecified access to the entire physical memory
#define M8(addr) (*(unsigned char volatile far*)(addr))		// macro definition for provision of 8-bit access to the entire physical memory
#define M16(addr) (*(unsigned short volatile far*)(addr))	// macro definition for provision of 16-bit access to the entire physical memory
#define M32(addr) (*(unsigned long volatile far*)(addr))	// macro definition for provision of 32-bit access to the entire physical memory

#define MEM_BLK_FREE	0	// (recommended value 0) free
#define MEM_BLK_ROM		15	// (ALL BITS MUST BE ONES) unimplemented or ROM; also used as bitmask for MEM_BLK_xxx constants

// set memory block status
// input
// (addr) memory address within the block
// (blk_status) two-bit block status (see MEM_BLK_xxx constants)
// output
// mem_map[] changed
void memory_set_status(unsigned long addr, unsigned char blk_status);

// get memory block status
// input
// (addr) memory address within the block
// output
// memory_get_status() block status according to the MEM_BLK_xxx constants
unsigned char memory_get_block(unsigned long addr);

// "quick" test of the entire memory and build memory map in mem_map[]
// NOTE: this function may take a while to finish and it is strongly recommended to disable watchdog operation during its execution
void memory_build_map(void);

// thorough test of specified memory area are return the number of usable bytes in it
// NOTE: this function may take a while to finish and it is strongly recommended to disable watchdog operation during its execution
// input
// (begin) absolute memory address from where to begin the test
// (length) length of the tested block; must be at least 4 bytes long
// output
// memory_test() number of available RAM bytes
unsigned long memory_test(unsigned long begin, unsigned long length);

// calculates the amount of currently free memory in bytes
// output
// memory_get_free() bytes of free memory
unsigned long memory_get_free(void);

#endif
