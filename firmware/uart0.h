#ifndef _UART0_H
#define _UART0_H

/* NOTE:
Not sure if this is a ZDS II bug, but in file PRINT_PUTCH.H which is a standard file supplied with ZDS II,
The line (*__print_xputch)(ch); in function __print_putch(), contains that extra asterisk which causes an
invalid reference call to the putch() function. After removing the asterisk everything works fine.
*/

#include <stdarg.h>

#define UART0_RX_BUFFER_SIZE 256

void uart0_init(unsigned long baudrate);
int putch(char ch);
char getch(void);
int kbhit(void);

#endif
