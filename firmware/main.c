#include <zneo.h>
#include <stdio.h>
#include "main.h"
#include "uart0.h"
#include "memory.h"
#include "spi.h"
#include "eve.h"

FLASH_OPTION3=0x7f;

unsigned char sys_flags=0;	// system flags (see SYS_FLG_xxx constants)


void main(void) {

	WDTH=0x55; WDTH=0xaa; WDTHL=10000;	// initialise the watchdog reload register for 1s interval

	OSCDIV=0x00;	// no divider for the oscillator
    OSCCTL=0xe7; OSCCTL=0x18;	// unlock the oscillator control
    OSCCTL=0xf8;	// enable the external crystal oscillator and prepare the watchdog for later use
	{ int t; for(t=0; t<50000; t++); }	// delay for crystal oscialltor stabilisation
	OSCCTL=0xe7; OSCCTL=0x18;	// unlock the oscillator control
    OSCCTL|=0x01;	// select the external crystal oscillator

	PADD=0x9f; PBDD=0xff; PCDD=0x63; PDDD=0x00; PEDD=0xff; PFDD=0x00; PGDD=0x00; PHDD=0xf0; PJDD=0x66; PKDD=0x00;	// set port directions
	PAHDE=0x03; PBHDE=0xff; PCHDE=0x03;	// enable high drive current for GP0..GP11 pints
	PAAFL=0xf0; PCAFL=0x38; PDAFH=0xff; PFAFL=0xff; PGAFL=0xff; PHAFH=0x03; PKAFL=0xff;	// set port functions
	PCOUT=0x04; PHOUT=0x0c; PJOUT=0x99;	// degault high state for some ports
	
	// these will be set by the linker
	// EXTCS0=0x9001; EXTCS1=0x9001; EXTCS2=0x9011; EXTCS3=0x9015; EXTCS4=0x9015; EXTCS5=0x9015;
	// EXTCT=0x40; 	// enable and configure the external interface

	memory_build_map();	// initialise and test the available memory and build memory map
	uart0_init(57600);	// initialise UART with default parameters (57600,8N1)

	

	printf("\r%d bytes free\r\n",memory_get_free());	// ### to be removed




	EI();	// enable interrupts	
	while(1) {

		


    
    }
}
