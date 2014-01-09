#include <zneo.h>
#include "eve.h"
#include "spi.h"	// EVE is controlled via SPI
#include "main.h"	// SPI device select signals in 16z are defined here


void eve_wr8(unsigned long addr, unsigned char d) {
	spi_select(EVE);
	addr&=0x3fffff;
	addr|=0x800000;	// write commands have '10' in bits [23,22]
	spi_rw((unsigned char)(addr>>16));
	spi_rw((unsigned char)(addr>>8));
	spi_rw((unsigned char)addr);
	spi_rw(d);
	spi_unselect();
}


void eve_wr16(unsigned long addr, unsigned short d) {
	spi_select(EVE);
	addr&=0x3fffff;
	addr|=0x800000;	// write commands have '10' in bits [23,22]
	spi_rw((unsigned char)(addr>>16));
	spi_rw((unsigned char)(addr>>8));
	spi_rw((unsigned char)addr);
	spi_rw((unsigned char)d);
	spi_rw((unsigned char)(d>>8));
	spi_unselect();
}


void eve_wr32(unsigned long addr, unsigned long d) {
	spi_select(EVE);
	addr&=0x3fffff;
	addr|=0x800000;	// write commands have '10' in bits [23,22]
	spi_rw((unsigned char)(addr>>16));
	spi_rw((unsigned char)(addr>>8));
	spi_rw((unsigned char)addr);
	spi_rw((unsigned char)d); 
	spi_rw((unsigned char)(d>>8)); 
	spi_rw((unsigned char)(d>>16)); 
	spi_rw((unsigned char)(d>>24));
	spi_unselect();
}


unsigned char eve_rd8(unsigned long addr) {
	unsigned char d;
	spi_select(EVE);
	addr&=0x3fffff;	// read commands have '00' in bits [23,22]
	spi_rw((unsigned char)(addr>>16));
	spi_rw((unsigned char)(addr>>8));
	spi_rw((unsigned char)addr);
	spi_rw(0);	// dummy byte
	d=spi_rw(0);
	spi_unselect();
	return d;
}


unsigned short eve_rd16(unsigned long addr) {
	unsigned short d;
	spi_select(EVE);
	addr&=0x3fffff;	// read commands have '00' in bits [23,22]
	spi_rw((unsigned char)(addr>>16));
	spi_rw((unsigned char)(addr>>8));
	spi_rw((unsigned char)addr);
	spi_rw(0);	// dummy byte
	d=((unsigned short)spi_rw(0)+((unsigned short)spi_rw(0)<<8));
	spi_unselect();
	return d;
}


unsigned long eve_rd32(unsigned long addr) {
	unsigned long d;
	spi_select(EVE);
	addr&=0x3fffff;	// read commands have '00' in bits [23,22]
	spi_rw((unsigned char)(addr>>16));
	spi_rw((unsigned char)(addr>>8));
	spi_rw((unsigned char)addr);
	spi_rw(0);	// dummy byte
	d=((unsigned long)spi_rw(0)+((unsigned long)spi_rw(0)<<8)+((unsigned long)spi_rw(0)<<16)+((unsigned long)spi_rw(0)<<24));
	spi_unselect();
	return d;
}


void eve_cmd(unsigned char cmd) {
	spi_select(EVE);
	cmd&=0x3f;
	cmd|=0x40;	// commands have '01' in bits [7,6]
	spi_rw(cmd);
	spi_rw(0);
	spi_rw(0);
	spi_unselect();
}


void eve_init(unsigned short xres, unsigned short yres) {





	
	eve_cmd(EVE_CMD_ACTIVE);
	eve_cmd(EVE_CMD_CLKEXT);
	eve_wr8(EVE_REG_GPIO,0x10);
	eve_wr8(EVE_REG_PCLK,2);

}
