/*
Toyaga 16z firmware v0.1
(C) 2014 Konstantin Dimitrov
*/

#ifndef _MAIN_H
#define _MAIN_H

#define SYS_CLK 18432000	// system clock in Hertz

#ifndef BIT
	#define BIT(x) (1<<(x))
#endif

// macro parameters for the SPI hardware in 16z; to be used with the spi_select() function
#define EXP &PCOUT,0x04		// expansion port
#define EVE &PJOUT,0x08		// A/V controller
#define RF  &PHOUT,0x04		// RF transceiver
#define SXM &PHOUT,0x08		// optional serial memory
#define SD0 &PJOUT,0x80		// uSD0 card
#define SD1 &PJOUT,0x01		// SD1 card
#define SD2 &PJOUT,0x10		// SD2 card

#define SYS_FLG_SERIAL_CONSOLE BIT(0)	// UART enabled as system console

extern unsigned char sys_flags;	// system flags (see SYS_FLG_xxx constants)

#endif
