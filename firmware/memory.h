#ifndef _MEMORY_H
#define _MEMORY_H

#define M(addr) (*(unsigned char volatile _Far*)(addr))	// macro definition for provision of byte access to the entire physical memory

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

// test the entire memory and build memory map in mem_map[]
void memory_build_map(void);

// calculates the amount of currently free memory in bytes
// output
// memory_get_free() bytes of free memory
unsigned long memory_get_free(void);

#endif
