#include <stdio.h>
#include <string.h>
#include "main.h"
#include "memory.h"

// NOTE: changing MEM_BLOCK_SIZE will require relevant changes in the other #define statements in this group
#define MEM_BLOCK_SIZE 0x1000	// memory block size
#define MEM_ABS_ADDRESS 0		// absolute physical address where the memory starts
#define MEM_MAP_SIZE 480		// number of indexes in mem_map[]; each index represents 8 blocks space
#define MEM_MAP_INDEX(addr)	((unsigned long)addr>>15)			// calculate index in mem_map[]
#define MEM_MAP_BIT(addr)	(((unsigned long)addr&0x7000)>>10)	// calculate start bit (L) in mem_map[]; the following bit is H


unsigned long mem_map[MEM_MAP_SIZE];	// memory map in blocks of MEM_BLOCK_SIZE bytes
										// each block is represented by four bits; see MEM_BLK_xxx constants


void memory_set_status(unsigned long addr, unsigned char blk_status) {
	unsigned short index=MEM_MAP_INDEX(addr);
	unsigned char mbit=MEM_MAP_BIT(addr);
	unsigned long mask=((unsigned long)MEM_BLK_ROM<<mbit);
	unsigned long stat=(((unsigned long)blk_status&MEM_BLK_ROM)<<mbit);
	mem_map[index]&=~mask;
	mem_map[index]|=stat;
}


unsigned char memory_get_status(unsigned long addr) {
	unsigned short index=MEM_MAP_INDEX(addr);
	unsigned char mbit=MEM_MAP_BIT(addr);
	return (unsigned char)(mem_map[index]>>mbit)&MEM_BLK_ROM;
}


void memory_build_map(void) {
	unsigned long addr,size=8*MEM_MAP_SIZE*MEM_BLOCK_SIZE;	// one 32-bit map cell represents eight memory blocks	
	memset((void *)MEM_ABS_ADDRESS,0xff,size);
	memset(mem_map,0xffffffff,sizeof(mem_map));
	for(addr=MEM_ABS_ADDRESS; addr<size; addr+=MEM_BLOCK_SIZE) {
		unsigned long b0,b1,b2;
		b0=M32(addr); M32(addr)=~M32(addr); b1=M32(addr); M32(addr)=~M32(addr); b2=M32(addr);
		memory_set_status(addr,(((b0+b1+b2) == (b0-1))? MEM_BLK_FREE : MEM_BLK_ROM));
	}
}


unsigned long memory_test(unsigned long begin, unsigned long length) {
	unsigned long mask[4]= {0xff690096, 0x12488421, 0xffffffff, 0x00000000};
	unsigned long addr, r=0;
	for(addr=begin; addr<=(begin+length-4); addr++) {		
		unsigned long z;
		unsigned char b,m=0;
		for(b=0; b<4; b++) {
			M32(addr)=mask[b];
			z=M32(addr);
			if(mask[b] == z) m++; else break;
		}
		if(m == 4) {
			r++;
			if(addr == (begin+length-4)) r+=3;
		}
	}
	return r;
}


unsigned long memory_get_free(void) {
	unsigned long r=0;
	unsigned short x;
	for(x=0; x<MEM_MAP_SIZE; x++) {
		unsigned long m=mem_map[x];
		unsigned char c=8;	// one 32-bit map cell represents eight memory blocks
		while(c--) {
			if((m&MEM_BLK_ROM) == MEM_BLK_FREE) r+=MEM_BLOCK_SIZE;
			m>>=4;
		}
	}
	return r;
}