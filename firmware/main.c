#include <zneo.h>
#include <stdio.h>
#include "main.h"
#include "uart0.h"
#include "memory.h"
#include "spi.h"

FLASH_OPTION3=0x7f;

unsigned char sys_flags=0;	// system flags (see SYS_FLG_xxx constants)


void main(void) {

	WDTH=0x55; WDTH=0xaa; WDTHL=10000;	// initialise the watchdog reload register for 1s interval

	OSCDIV=0x00;	// no divider for the oscillator
    OSCCTL=0xe7; OSCCTL=0x18;	// unlock the oscillator control
    OSCCTL=0xf8;	// enable the external crystal oscillator and prepare the watchdog for later use
    asm("LD R0,#500000");   // a small delay for crystal oscillator stabilisation
    asm("label1: NOP");
    asm("DJNZ R0,label1");
	OSCCTL=0xe7; OSCCTL=0x18;	// unlock the oscillator control
    OSCCTL|=0x01;	// select the external crystal oscillator

	PADD=0xff; PBDD=0xff; PCDD=0x7b; PDDD=0xff; PEDD=0xff; PFDD=0xff; PGDD=0xff; PHDD=0xf3; PJDD=0x66; PKDD=0xff;	// set port directions
	PAHDE=0xff; PBHDE=0xff; PCHDE=0xff; PDHDE=0xff; PEHDE=0xff; PFHDE=0xff; PGHDE=0xff; PHHDE=0xff; PJHDE=0xff; PKHDE=0xff; // enable high current drive for all ports
	PAAFL=0xf0; PCAFL=0x38; PDAFH=0xff; PFAFL=0xff; PGAFL=0xff; PHAFH=0x03; PKAFL=0xfd;	// set port functions
	PCOUT=0xff; PHOUT=0xff; PJOUT=0xff;	// default high state for some ports
	
	// these will be set by the linker anyway
	EXTCS0=0x9001; EXTCS1=0x9001; EXTCS2=0x9011; EXTCS3=0x9015; EXTCS4=0x9015; EXTCS5=0x9015;
	EXTCT=0x40; 	// enable and configure the external interface
    
    // ==================== no C variables before this point since the external bus won't be configured yet ============================


	uart0_init(57600);	// initialise UART with default parameters (57600,8N1)

	memory_build_map();	// initialise and test the available memory and build memory map


	// ### for testing only - to be removed
	printf("\rTesting RAM ");
	{	
		unsigned long step=0x10000;
		unsigned long a, z=0;		
		for(a=0; a<0xf00000; a+=step) {
			z+=memory_test(a,step);
			printf("\r%d bytes free ",z);
		}
	}
	printf("\r\nDone.\r\n\n");





	EI();	// enable interrupts	
	while(1) {

		


    
    }
}
