/*
ZNEO single master SPI functions
(C) 2014 Konstantin Dimitrov
*/

#ifndef _SPI_H
#define _SPI_H

// basic SPI initialisation in mode 0; SCLK rate at 1/2 the system clock i.e. 9.216MHz
void spi_init(void);

// unselect all SPI devices
void spi_unselect(void);

// select an SPI device
void spi_select(unsigned char volatile near *port, unsigned char mask);

// read/write SPI data (single byte; polled)
// input
// (data) data byte to be written to SPI
// output
// spi_rw() bits 15..8: current value of ESPISTAT with cleared TFST and SLAS bits ($fc mask)
//			bits 7..0: data byte read from SPI
unsigned short spi_rw(unsigned char data);

#endif
