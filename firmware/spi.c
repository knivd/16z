#include <zneo.h>
#include <stdio.h>
#include "spi.h"

unsigned char volatile near *spi_select_port=NULL;	// port of ~SS for the currently selected SPI device
unsigned char spi_select_mask=0;	// ~SS mask for the currently selected SPI device (only if *spi_select_port != NULL)


void spi_init(void) {
	PCDD|=0x38; PCAFL|=0x38; PCAFH&=~0x38;	// ~SS pin is not initialised as part of the SPI here
	ESPICTL=0x00;
	ESPIBR=0x0001;
	ESPIMODE=0x02;
	ESPICTL=0x43;
}


void spi_unselect(void) {
	if(spi_select_port) {
		*spi_select_port|=spi_select_mask;
		spi_select_port=NULL;
	}
}


void spi_select(unsigned char volatile near *port, unsigned char mask) {
	spi_unselect();
	if(port && mask) {
		spi_select_port=port;
		spi_select_mask=mask;
		(*port)&=~mask;
	}
}


unsigned short spi_rw(unsigned char data) {
	unsigned char s,r=0;
	while(ESPISTAT & 0x02);	// wait here if there is an ongoing transfer
	if(ESPISTAT & 0x04) r=ESPIDATA;
	if(ESPISTAT & 0x80) ESPIDATA=data;
	s=(ESPISTAT&0xfc);
	return ((unsigned short)s<<8)+r;
}
