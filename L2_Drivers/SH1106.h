/*
 * SH1106.h
 *
 *  Created on: Aug 10, 2018
 *      Author: rehanashraf
 */

#ifndef LIB_L2_DRIVERS_SH1106_H_
#define LIB_L2_DRIVERS_SH1106_H_

#include "gpio.hpp"
#include "tasks.hpp"
#include "ssp1.h"
#include "cstring"
#include "utilities.h"
#include "GFX.h"

//#define HAVE_PORTREG

#ifdef HAVE_PORTREG
typedef volatile uint8_t PortReg;
typedef uint8_t PortMask;
#endif

#define BLACK 0
#define WHITE 1
#define INVERSE 2

typedef bool boolean;
typedef uint8_t byte;

#define SH1106_128_64
//#define SH1106_128_32
//#define SH1106_96_16


#if defined SH1106_128_64
  #define SH1106_LCDWIDTH                  128
  #define SH1106_LCDHEIGHT                 64
#endif
#if defined SH1106_128_32
  #define SH1106_LCDWIDTH                  128
  #define SH1106_LCDHEIGHT                 32
#endif
#if defined SH1106_96_16
  #define SH1106_LCDWIDTH                  96
  #define SH1106_LCDHEIGHT                 16
#endif

#define SH1106_SETCONTRAST 0x81
#define SH1106_DISPLAYALLON_RESUME 0xA4
#define SH1106_DISPLAYALLON 0xA5
#define SH1106_NORMALDISPLAY 0xA6
#define SH1106_INVERTDISPLAY 0xA7
#define SH1106_DISPLAYOFF 0xAE
#define SH1106_DISPLAYON 0xAF
#define SH1106_OUTPUT_FOLLOWS_RAM 0xA4


#define SH1106_SETDISPLAYOFFSET 0xD3
#define SH1106_SETCOMPINS 0xDA

#define SH1106_SETVCOMDETECT 0xDB

#define SH1106_SETDISPLAYCLOCKDIV 0xD5
#define SH1106_SETPRECHARGE 0xD9

#define SH1106_SETMULTIPLEX 0xA8

#define SH1106_SETLOWCOLUMN 0x00
#define SH1106_SETHIGHCOLUMN 0x10
#define SH1106_SET_SEGMENT_REMAP	0xA1 // 0 to 127

#define SH1106_SETSTARTLINE 0x40

#define SH1106_MEMORYMODE 0x20
#define SH1106_COLUMNADDR 0x21
#define SH1106_PAGEADDR   0x22
#define SH1106_SET_PAGE_ADDRESS	0xB0 /* sets the page address from 0 to 7 */

#define SH1106_COMSCANINC 0xC0
#define SH1106_COMSCANDEC 0xC8

#define SH1106_SEGREMAP 0xA0

#define SH1106_CHARGEPUMP 0x8D

#define SH1106_EXTERNALVCC 0x1
#define SH1106_SWITCHCAPVCC 0x2

// Scrolling #defines
#define SH1106_ACTIVATE_SCROLL 0x2F
#define SH1106_DEACTIVATE_SCROLL 0x2E
#define SH1106_SET_VERTICAL_SCROLL_AREA 0xA3
#define SH1106_RIGHT_HORIZONTAL_SCROLL 0x26
#define SH1106_LEFT_HORIZONTAL_SCROLL 0x27
#define SH1106_VERTICAL_AND_RIGHT_HORIZONTAL_SCROLL 0x29
#define SH1106_VERTICAL_AND_LEFT_HORIZONTAL_SCROLL 0x2A

#define SH1106_MAX_PAGE_COUNT  8
//#define USING_SW_SPI
//#define GFX_IMPLEMENTED


class SH1106 : public GFX//: public scheduler_task
{
public:
	SH1106();
	virtual ~SH1106();
	SH1106(GPIO *DC, GPIO *RST, GPIO *CS);
	/*********: scheduler_task("sh1106", 2000, PRIORITY_LOW)
	{
		sid = SID;
		dc = DC;
		rst = RST;
		cs = CS;
		sclk = SCLK;
		mosiport = clkport = csport = dcport = NULL;
		mosipinmask = clkpinmask = cspinmask = dcpinmask = _i2caddr = _vccstate = 0;
		hwSPI = false;
	}; // This is the scheduler_task implementation of SH1106
	bool init(void);
	bool run (void *p);
	****************/
#ifdef USING_SW_SPI
	SH1106(GPIO *DC, GPIO *RST, GPIO *CS, GPIO *CLK, GPIO *MOSI);
#endif
	void init(uint8_t switchvcc = SH1106_SWITCHCAPVCC);
	void sh1106_command(uint8_t c);
	void setCustomDisplay(void);
	void clearDisplay(void);
	void setAdafruitDisplay(void);
	void invertDisplay(uint8_t i);
	void display();

	void startscrollright(uint8_t start, uint8_t stop);
	void startscrollleft(uint8_t start, uint8_t stop);

	void startscrolldiagright(uint8_t start, uint8_t stop);
	void startscrolldiagleft(uint8_t start, uint8_t stop);
	void stopscroll(void);

	void dim(boolean dim);

	void drawPixel(int16_t x, int16_t y, uint16_t color);

#ifdef GFX_IMPLEMENTED
	virtual void drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color);
	virtual void drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color);
#endif
private:
	GPIO  *dc, *rst, *cs;
#ifdef USING_SW_SPI
	GPIO *clk, *mosi;
#endif


	void fastSPIwrite(uint8_t c); /* This is the Software SPI implmentation of */
	uint8_t _vccstate;

//	boolean hwSPI; /* Use to store the value of Hardware SPI and Software SPI */
#ifdef HAVE_PORTREG
	PortReg *mosiport, *clkport, *csport, *dcport;
	PortMask mosipinmask, clkpinmask, cspinmask, dcpinmask;
#endif

	inline void drawFastVLineInternal(int16_t x, int16_t y, int16_t h, uint16_t color) __attribute__((always_inline));
	inline void drawFastHLineInternal(int16_t x, int16_t y, int16_t w, uint16_t color) __attribute__((always_inline));
};

#endif /* LIB_L2_DRIVERS_SH1106_H_ */
