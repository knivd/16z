#ifndef _MAIN_H
#define _MAIN_H

#define SYS_CLK 18432000	// system clock in Hertz

#ifndef BIT
	#define BIT(x) (1<<(x))
#endif

#define SYS_FLG_SERIAL_CONSOLE BIT(0)	// UART enabled as system console

extern unsigned char sys_flags;	// system flags (see SYS_FLG_xxx constants)

#endif
