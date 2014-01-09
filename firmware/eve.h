#ifndef _EVE_H
#define _EVE_H

#define EVE_VRAM_ADDR 	0x000000	// video RAM start address
#define EVE_VRAM_SIZE 	0x03ffff	// video RAM size in bytes
#define EVE_CHIP_ID		0x0c0000	// ROM; unsigned long; chip identifier
#define EVE_FONT_ADDR	0x0ffffc	// ROM; unsigned long; font table pointer address
#define EVE_FONT_SIZE	0x044dc0	// font table size in bytes
#define EVE_DLRAM_ADDR	0x100000	// display list RAM start address
#define EVE_DLRAM_SIZE	0x1fff		// display list RAM size in bytes
#define EVE_PAL_ADDR	0x102000	// palette RAM start address
#define EVE_PAL_SIZE	0x0400		// palette RAM size in bytes
#define EVE_REGISTERS	0x102400	// internal registers start address
#define EVE_BUFFER_ADDR	0x108000	// command buffer start address
#define EVE_BUFFER_SIZE	0x1000		// command buffer size in bytes

#define RGB(r,g,b) ((((unsigned long)(r))<<16) | (((unsigned long)(g))<<8) | (b))

// command codes
#define EVE_CMD_ACTIVE	0x00
#define EVE_CMD_STANDBY	0x41
#define EVE_CMD_SLEEP	0x42
#define EVE_CMD_PWRDOWN	0x50
#define EVE_CMD_CLKEXT	0x44
#define EVE_CMD_CLK48M	0x62
#define EVE_CMD_CLK36M	0x61
#define EVE_CMD_CORERST	0x68

// internal register addresses
#define EVE_REG_ID					0x102400
#define EVE_REG_FRAMES				0x102404
#define EVE_REG_CLOCK				0x102408
#define EVE_REG_FREQUENCY			0x10240C
#define EVE_REG_RENDERMODE			0x102410
#define EVE_REG_SNAPY				0x102414
#define EVE_REG_SNAPSHOT			0x102418
#define EVE_REG_CPURESET			0x10241C
#define EVE_REG_TAP_CRC				0x102420
#define EVE_REG_TAP_MASK			0x102424
#define EVE_REG_HCYCLE				0x102428
#define EVE_REG_HOFFSET				0x10242C
#define EVE_REG_HSIZE				0x102430
#define EVE_REG_HSYNC0				0x102434
#define EVE_REG_HSYNC1				0x102438
#define EVE_REG_VCYCLE				0x10243C
#define EVE_REG_VOFFSET				0x102440
#define EVE_REG_VSIZE				0x102444
#define EVE_REG_VSYNC0				0x102448
#define EVE_REG_VSYNC1				0x10244C
#define EVE_REG_DLSWAP				0x102450
#define EVE_REG_ROTATE				0x102454
#define EVE_REG_OUTBITS				0x102458
#define EVE_REG_DITHER				0x10245C
#define EVE_REG_SWIZZLE				0x102460
#define EVE_REG_CSPREAD				0x102464
#define EVE_REG_PCLK_POL			0x102468
#define EVE_REG_PCLK				0x10246C
#define EVE_REG_TAG_X				0x102470
#define EVE_REG_TAG_Y				0x102474
#define EVE_REG_TAG					0x102478
#define EVE_REG_VOL_PB				0x10247C
#define EVE_REG_VOL_SOUND			0x102480
#define EVE_REG_SOUND				0x102484
#define EVE_REG_PLAY				0x102488
#define EVE_REG_GPIO_DIR			0x10248C
#define EVE_REG_GPIO				0x102490
#define EVE_Reserved				0x102494
#define EVE_REG_INT_FLAGS			0x102498
#define EVE_REG_INT_EN				0x10249C
#define EVE_REG_INT_MASK			0x1024A0
#define EVE_REG_PLAYBACK_START		0x1024A4
#define EVE_REG_PLAYBACK_LENGTH		0x1024A8
#define EVE_REG_PLAYBACK_READPTR	0x1024AC
#define EVE_REG_PLAYBACK_FREQ		0x1024B0
#define EVE_REG_PLAYBACK_FORMAT		0x1024B4
#define EVE_REG_PLAYBACK_LOOP		0x1024B8
#define EVE_REG_PLAYBACK_PLAY		0x1024BC
#define EVE_REG_PWM_HZ				0x1024C0
#define EVE_REG_PWM_DUTY			0x1024C4
#define EVE_REG_MACRO_0				0x1024C8
#define EVE_REG_MACRO_1				0x1024CC
#define EVE_REG_CMD_READ			0x1024E4
#define EVE_REG_CMD_WRITE			0x1024E8
#define EVE_REG_CMD_DL				0x1024EC
#define EVE_REG_TOUCH_MODE			0x1024F0
#define EVE_REG_TOUCH_ADC_MODE		0x1024F4
#define EVE_REG_TOUCH_CHARGE		0x1024F8
#define EVE_REG_TOUCH_SETTLE		0x1024FC
#define EVE_REG_TOUCH_OVERSAMPLE	0x102500
#define EVE_REG_TOUCH_RZTHRESH		0x102504
#define EVE_REG_TOUCH_RAW_XY		0x102508
#define EVE_REG_TOUCH_RZ			0x10250C
#define EVE_REG_TOUCH_SCREEN_XY		0x102510
#define EVE_REG_TOUCH_TAG_XY		0x102514
#define EVE_REG_TOUCH_TAG			0x102518
#define EVE_REG_TOUCH_TRANSFORM_A	0x10251C
#define EVE_REG_TOUCH_TRANSFORM_B	0x102520
#define EVE_REG_TOUCH_TRANSFORM_C	0x102524
#define EVE_REG_TOUCH_TRANSFORM_D	0x102528
#define EVE_REG_TOUCH_TRANSFORM_E	0x10252C
#define EVE_REG_TOUCH_TRANSFORM_F	0x102530
#define EVE_REG_TOUCH_DIRECT_XY		0x102574
#define EVE_REG_TOUCH_DIRECT_Z1Z2	0x102578
#define EVE_REG_TRACKER				0x109000

// low level communication functions
void eve_wr8(unsigned long addr, unsigned char d);
void eve_wr16(unsigned long addr, unsigned short d);
void eve_wr32(unsigned long addr, unsigned long d);
unsigned char eve_rd8(unsigned long addr);
unsigned short eve_rd16(unsigned long addr);
unsigned long eve_rd32(unsigned long addr);
void eve_cmd(unsigned char cmd);	// see EVE_CMD_xxx constants

// initialise the EVE controller
// input
// (xres,yres) desired X and Y resolution in pixels
void eve_init(unsigned short xres, unsigned short yres);

#endif
