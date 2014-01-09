#include <zneo.h>
#include <stdio.h>
#include "uart0.h"
#include "main.h"

static unsigned char buffer[UART0_RX_BUFFER_SIZE];
static unsigned short index_in=0;	// points the next free position in the reception buffer
static unsigned short index_out=0;	// points the current occupied cell in the buffer


void interrupt uart0_rx(void) {
	if(U0STAT0 & 0x80) {
		buffer[index_in++]=U0RXD;
		if(index_in >= UART0_RX_BUFFER_SIZE) index_in=0;	
	}
}


void uart0_init(unsigned long baudrate) {
	unsigned long b=SYS_CLK/(16*baudrate);
	PADD|=0x30; PAAFL|=0x30; PAAFH&=~0x30;
	U0CTL0=0x00;
	U0BR=(unsigned short)b;
	U0MDSTAT=0x00;	
	U0CTL1=0x00;	
	U0CTL0=0xc0;
	SET_VECTOR(UART0_RX,uart0_rx);
	IRQ0EN&=~0x1010; IRQ0ENH|=0x10;	// enable reception interrupts (only) with normal priority
}


int putch(char ch) {
	while((U0STAT0&0x02) == 0);	// wait until the transmit register is available for new data
	U0TXD=(unsigned char)ch;
	return 0;
}


int kbhit(void) {
	return ((index_in != index_out)? 1 : 0);
}


char getch(void) {
	char d=0;
	while(kbhit() == 0);	// wait for new character in the buffer
	if(kbhit()) {
		d=(char)buffer[index_out++];
		if(index_out >= UART0_RX_BUFFER_SIZE) index_out=0;	
	}
	return d;
}
