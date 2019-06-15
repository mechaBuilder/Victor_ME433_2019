#include <xc.h>
#include "ili9341.h"
#include<math.h>

// spi pins
#define CS LATBbits.LATB7
#define DC LATBbits.LATB15

void LCD_init() {
    int time = 0;
    
    CS = 0; // CS
   
    LCD_command(ILI9341_SWRESET);
    time = _CP0_GET_COUNT();
    while (_CP0_GET_COUNT() < time + 7200000) {} // 300ms

    LCD_command(0xEF);
  	LCD_data(0x03);
	LCD_data(0x80);
	LCD_data(0x02);
    time = _CP0_GET_COUNT();
    while (_CP0_GET_COUNT() < time + 3600000) {} // 150ms
    
    LCD_command(0xCF);
  	LCD_data(0x00);
	LCD_data(0xC1);
	LCD_data(0x30);
    time = _CP0_GET_COUNT();
    while (_CP0_GET_COUNT() < time + 3600000) {} // 150ms
    
    LCD_command(0xED);
  	LCD_data(0x64);
	LCD_data(0x03);
	LCD_data(0x12);
    LCD_data(0x81);
    time = _CP0_GET_COUNT();
    while (_CP0_GET_COUNT() < time + 3600000) {} // 150ms
    
    LCD_command(0xE8);
  	LCD_data(0x85);
	LCD_data(0x00);
	LCD_data(0x78);
    time = _CP0_GET_COUNT();
    while (_CP0_GET_COUNT() < time + 3600000) {} // 150ms
    
    LCD_command(0xCB);
  	LCD_data(0x39);
	LCD_data(0x2C);
	LCD_data(0x00);
    LCD_data(0x34);
    LCD_data(0x02);
    time = _CP0_GET_COUNT();
    while (_CP0_GET_COUNT() < time + 3600000) {} // 150ms
    
    LCD_command(0xF7);
  	LCD_data(0x20);
    time = _CP0_GET_COUNT();
    while (_CP0_GET_COUNT() < time + 3600000) {} // 150ms
    
    LCD_command(0xEA);
  	LCD_data(0x00);
	LCD_data(0x00);
    time = _CP0_GET_COUNT();
    while (_CP0_GET_COUNT() < time + 3600000) {} // 150ms
    
    LCD_command(ILI9341_PWCTR1);
  	LCD_data(0x23);
    time = _CP0_GET_COUNT();
    while (_CP0_GET_COUNT() < time + 3600000) {} // 150ms
    
    LCD_command(ILI9341_PWCTR2);
  	LCD_data(0x10);
    time = _CP0_GET_COUNT();
    while (_CP0_GET_COUNT() < time + 3600000) {} // 150ms
    
    LCD_command(ILI9341_VMCTR1 );
  	LCD_data(0x3e);
    LCD_data(0x28);
    time = _CP0_GET_COUNT();
    while (_CP0_GET_COUNT() < time + 3600000) {} // 150ms
    
    LCD_command(ILI9341_VMCTR2);
  	LCD_data(0x86);
    time = _CP0_GET_COUNT();
    while (_CP0_GET_COUNT() < time + 3600000) {} // 150ms
    
    LCD_command(ILI9341_MADCTL);
  	LCD_data(0x48);
    time = _CP0_GET_COUNT();
    while (_CP0_GET_COUNT() < time + 3600000) {} // 150ms
/*    
    LCD_command(ILI9341_VSCRSADD);
  	LCD_data(0x00);
    time = _CP0_GET_COUNT();
    while (_CP0_GET_COUNT() < time + 3600000) {} // 150ms
 */   
    LCD_command(ILI9341_PIXFMT);
  	LCD_data(0x55);
    time = _CP0_GET_COUNT();
    while (_CP0_GET_COUNT() < time + 3600000) {} // 150ms
    
    LCD_command(ILI9341_FRMCTR1);
  	LCD_data(0x00);
    LCD_data(0x18);
    time = _CP0_GET_COUNT();
    while (_CP0_GET_COUNT() < time + 3600000) {} // 150ms
    
    LCD_command( ILI9341_DFUNCTR);
  	LCD_data(0x08);
    LCD_data(0x82);
    LCD_data(0x27);
    time = _CP0_GET_COUNT();
    while (_CP0_GET_COUNT() < time + 3600000) {} // 150ms
    
    LCD_command(0xF2);
  	LCD_data(0); // 1
    LCD_data(0x00);
    time = _CP0_GET_COUNT();
    while (_CP0_GET_COUNT() < time + 3600000) {} // 150ms
    
    LCD_command(ILI9341_GAMMASET);
  	LCD_data(0x01);
    time = _CP0_GET_COUNT();
    while (_CP0_GET_COUNT() < time + 3600000) {} // 150ms
    
    LCD_command(ILI9341_GMCTRP1);
  	LCD_data(0x0F);
    LCD_data(0x31);
    LCD_data(0x2B);
    LCD_data(0x0C);
    LCD_data(0x0E);
    LCD_data(0x08);
    LCD_data(0x4E);
    LCD_data(0xF1);
    LCD_data(0x37);
    LCD_data(0x07);
    LCD_data(0x10);
    LCD_data(0x03);
    LCD_data(0x0E);
    LCD_data(0x09);
    LCD_data(0x00);
    time = _CP0_GET_COUNT();
    while (_CP0_GET_COUNT() < time + 3600000) {} // 150ms
    
    LCD_command(ILI9341_GMCTRN1);
  	LCD_data(0x00);
    LCD_data(0x0E);
    LCD_data(0x14);
    LCD_data(0x03);
    LCD_data(0x11);
    LCD_data(0x07);
    LCD_data(0x31);
    LCD_data(0xC1);
    LCD_data(0x48);
    LCD_data(0x08);
    LCD_data(0x0F);
    LCD_data(0x0C);
    LCD_data(0x31);
    LCD_data(0x36);
    LCD_data(0x0F);
    time = _CP0_GET_COUNT();
    while (_CP0_GET_COUNT() < time + 3600000) {} // 150ms
    
    LCD_command(0xB1);
  	LCD_data(0x00);
    LCD_data(0x10);
    time = _CP0_GET_COUNT();
    while (_CP0_GET_COUNT() < time + 3600000) {} // 150ms
    
    LCD_command(ILI9341_SLPOUT);
    time = _CP0_GET_COUNT();
    while (_CP0_GET_COUNT() < time + 3600000) {} // 150ms
    
    LCD_command(ILI9341_DISPON);
    
    CS = 1; // CS
    time = _CP0_GET_COUNT();
    while (_CP0_GET_COUNT() < time + 3600000) {} // 150ms
    
    
    CS = 0; // CS
    
    LCD_command(ILI9341_MADCTL);
    LCD_data(MADCTL_MX | MADCTL_BGR); // rotation
    time = _CP0_GET_COUNT();
    while (_CP0_GET_COUNT() < time + 3600000) {} // 150ms
    
    CS = 1; // CS
}

void SPI1_init() {
  SDI1Rbits.SDI1R = 0b0100; // B8 is SDI1
  RPA1Rbits.RPA1R = 0b0011; // A1 is SDO1
  TRISBbits.TRISB7 = 0; // CS is B7
  CS = 1; // CS starts high

  // DC pin
  TRISBbits.TRISB15 = 0;
  DC = 1;
  
  SPI1CON = 0; // turn off the spi module and reset it
  SPI1BUF; // clear the rx buffer by reading from it
  SPI1BRG = 0; // baud rate to 12 MHz [SPI1BRG = (48000000/(2*desired))-1]
  SPI1STATbits.SPIROV = 0; // clear the overflow bit
  SPI1CONbits.CKE = 1; // data changes when clock goes from hi to lo (since CKP is 0)
  SPI1CONbits.MSTEN = 1; // master operation
  SPI1CONbits.ON = 1; // turn on spi1
}

unsigned char spi_io(unsigned char o) {
  SPI1BUF = o;
  while(!SPI1STATbits.SPIRBF) { // wait to receive the byte
    ;
  }
  return SPI1BUF;
}

void LCD_command(unsigned char com) {
    DC = 0; // DC
    spi_io(com);
    DC = 1; // DC
}

void LCD_data(unsigned char dat) {
    spi_io(dat);
}

void LCD_data16(unsigned short dat) {
    spi_io(dat>>8);
    spi_io(dat);
}

void LCD_setAddr(unsigned short x, unsigned short y, unsigned short w, unsigned short h) {
    LCD_command(ILI9341_CASET); // Column
    LCD_data16(x);
	LCD_data16(x+w-1);

	LCD_command(ILI9341_PASET); // Page
	LCD_data16(y);
	LCD_data16(y+h-1);

	LCD_command(ILI9341_RAMWR); // Into RAM
}

void LCD_drawPixel(unsigned short x, unsigned short y, unsigned short color) {
  // check boundary
    
    CS = 0; // CS
    
    LCD_setAddr(x,y,1,1);
    LCD_data16(color);
    
    CS = 1; // CS
}

void LCD_clearScreen(unsigned short color) {
    int i;
    
    CS = 0; // CS
    
    LCD_setAddr(0,0,ILI9341_TFTWIDTH,ILI9341_TFTHEIGHT);
	for (i = 0;i < ILI9341_TFTWIDTH*ILI9341_TFTHEIGHT; i++){
		LCD_data16(color);
	}
    
    CS = 1; // CS
}

void drawLetter(char letter, unsigned short x, unsigned short y, unsigned c1, unsigned c2) {
    unsigned short i = 0, j = 0;
    for (i=0; i<5; i++) {
        char color = ASCII[letter - 0x20][i];
        for (j=0; j<7; j++) {
            char bit = ((color >> j) & 1); 
            if (bit == 1) {
                LCD_drawPixel(x+i, y+j, c1);            // c1 & c2 are colors
            }
            else {
                LCD_drawPixel(x+i, y+j, c2);
            }
        }
    }
}

void print2LCD(char *message, unsigned short x, unsigned short y, unsigned c1, unsigned c2) {
    unsigned short k = 0;
        while(message[k]){ 
            //display_character(array[i]); 
            drawLetter(message[k], x + (5*k), y, c1, c2); // each letter has 5 spaces
            k++;
        }
}

void barX(unsigned short x, unsigned short y, unsigned short length, signed short Ax, unsigned c1, unsigned c2) {
    unsigned short m = 0, n = 0, l = 0, neg = 0;
    for (n=0; n<=length; n++) {
        for (m=0; m<7; m++) {  //height       
            LCD_drawPixel(x + n, y+m, c1);
            LCD_drawPixel(x - n, y+m, c1);
            if (Ax >= 0) {
                for (l = 0; l <= Ax; l++) {
                    LCD_drawPixel(x + l, y+m, c2);
                }
            }
            if (Ax < 0){ 
                for (neg = 0; neg <= abs(Ax); neg++) {
                    LCD_drawPixel(x - neg, y+m, c2);
                }
            } 
        }
    }
}

void barY(unsigned short x, unsigned short y, unsigned short length, signed short Ay, unsigned c1, unsigned c2) {
    unsigned short m = 0, n = 0, l = 0, neg =0;
    for (n=0; n<=length; n++) {
        for (m=0; m<7; m++) {  //height       
            LCD_drawPixel(x + m, y+n, c1);
            LCD_drawPixel(x + m, y-n+8, c1);
            if (Ay >= 0) {
                for (l = 0; l <= Ay; l++) {
                    LCD_drawPixel(x + m, y+l, c2);
                }
            }
            if (Ay < 0){ 
                for (neg = 0; neg <= abs(Ay); neg++) {
                    LCD_drawPixel(x + m, y-neg, c2);
                }
            }
        }
    }
}

void LCDprintRow(unsigned short xCoord, unsigned short yCoord) {
    unsigned short x, y, pixel;
    unsigned short pixelArray[240] = {2,6,1,3,1,2,1,2,1,2,2,1,5,7,7,2,4,3,4,2,1,4,2,1,7,4,7,6,1,5,5,5,4,2,6,2,3,7,6,3,3,5,7,7,5,3,6,4,7,1,4,6,2,3,2,3,3,4,1,4,2,2,2,2,7,7,6,6,2,3,2,1,3,5,5,4,4,3,4,6,6,5,6,5,1,4,3,1,2,2,5,4,5,2,1,4,2,7,7,3,1,5,6,7,1,4,5,5,6,5,6,3,5,1,1,7,2,5,7,2,2,3,7,3,2,2,3,3,1,4,1,5,1,5,6,2,4,4,1,4,5,2,6,7,6,4,2,6,2,7,5,5,2,1,2,7,7,5,6,2,5,6,3,7,1,3,4,1,6,4,4,6,7,6,3,4,6,1,1,2,4,7,5,3,3,6,7,5,2,1,6,5,7,1,5,2,6,2,4,3,6,5,2,3,1,5,4,2,2,4,7,4,1,1,6,4,3,6,3,4,5,7,3,5,7,1,5,3,3,2,6,7,2,6,2,7,6,3,6,4};

    for (x = 0; x <= 240; x++) {
        pixel = pixelArray[x];// >> 5;      //remove 5 least significant bits (keep 3 most significant bits), resolution
        for (y = 0; y <8; y++) {
            if (y == pixel) {
                LCD_drawPixel(x, y+30, ILI9341_BLACK);
            }
            else {
                LCD_drawPixel(x, y+30, ILI9341_WHITE);
            }   
        }
    }
}


