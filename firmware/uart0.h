/*
ZNEO UART functions (UART0 only as supported by Toyaga 16z)
(C) 2014 Konstantin Dimitrov
*/

#ifndef _UART0_H
#define _UART0_H

/* NOTE:
Not sure if this is a ZDS II bug, but in file PRINT_PUTCH.H which is a standard file supplied with ZDS II,
The line (*__print_xputch)(ch); in function __print_putch(), contains that extra asterisk which causes an
invalid reference call to the putch() function. After removing the asterisk everything works fine.
*/

#define UART0_RX_BUFFER_SIZE 256	// UART0 reception buffer size in bytes

// initialise and enable UART0
// input
// (baudrate) desired baudrate in bps; data protocol is fixed at 8N1
void uart0_init(unsigned long baudrate);

// standard C functions for input/output
int putch(char ch);
int kbhit(void);	// unblocking test
char getch(void);	// blocking read

#endif
