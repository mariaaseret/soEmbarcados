/********************************************************************

16X2 ALPHANEUMERIC LCD INTERFACING LIBRARY FOR PIC 18F MCUS
-----------------------------------------------------------

Easy to use library for interfacing 16x2 lcd in 4 bit mode.

MCU: PIC18FXXXX Series from Microchip.
Compiler: HI-TECH C Compiler for PIC18 MCUs (http://www.htsoft.com/)

Copyrights 2008-2009 Avinash Gupta
eXtreme Electronics, India

For More Info visit
http://www.eXtremeElectronics.co.in

Mail: me@avinashgupta.com

********************************************************************/


#ifndef _LCD_H
#define _LCD_H

#include <htc.h>

#define _XTAL_FREQ 20000000UL

#include "myutils.h"

typedef unsigned char uint8_t;

/*_________________________________________________________________________________________*/

/************************************************
	LCD CONNECTIONS
*************************************************/

#define LCD_DATA D	//Port PD0-PD3 are connected to D4-D7

#define LCD_E D 	//Enable/strobe signal
#define LCD_E_POS	4	//Position of enable in above port

#define LCD_RS B	
#define LCD_RS_POS 1

#define LCD_RW B
#define LCD_RW_POS 2


//************************************************

#define LS_BLINK 0B00000001
#define LS_ULINE 0B00000010



/***************************************************
			F U N C T I O N S
****************************************************/



void LCDInit(uint8_t style);
void LCDWriteString(const char *msg);
void LCDWriteInt(int val,unsigned int field_length);
void LCDGotoXY(uint8_t x,uint8_t y);

//Low level
void LCDByte(uint8_t,uint8_t);
#define LCDCmd(c) (LCDByte(c,0))
#define LCDData(d) (LCDByte(d,1))

void LCDBusyLoop();



/***************************************************
			F U N C T I O N S     E N D
****************************************************/


/***************************************************
	M A C R O S
***************************************************/
#define LCDClear() LCDCmd(0b00000001)
#define LCDHome() LCDCmd(0b00000010)

#define LCDWriteStringXY(x,y,msg) {\
 LCDGotoXY(x,y);\
 LCDWriteString(msg);\
}

#define LCDWriteIntXY(x,y,val,fl) {\
 LCDGotoXY(x,y);\
 LCDWriteInt(val,fl);\
}
/***************************************************/




/*_________________________________________________________________________________________*/
#endif




