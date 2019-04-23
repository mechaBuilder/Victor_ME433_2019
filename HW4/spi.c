#include"spi.h"

// send a byte via spi and return the response
unsigned char spi_io(unsigned char ch) {
    SPI1BUF = ch;
    while(!SPI1STATbits.SPIRBF) {;} // wait to receive the byte
    return SPI1BUF;
}

// initialize SPI1
void SPI_init() {
    // Master - SPI1, pins are: SDI1(B11), SDO1(B13), SCK1(B14).  
    // we manually control SS1 as a digital output (B15)
    RPB13Rbits.RPB13R = 0b0011; // set DCO1 to B13 (pin 26) )
    SDI1Rbits.SDI1R = 0b0100; // Set SDI1 to B8, actually not connected to DAC
    SPI1CON = 0;              // turn off the SPI module and reset it
    SPI1BUF;                  // clear the rx buffer by reading from it
    SPI1BRG = 0x1;            // SPI1BRG = (48MHz/(2*x MHz))-1 = 1; now x = 12MHz
    SPI1STATbits.SPIROV = 0;  // clear the overflow bit
    SPI1CONbits.CKE = 1;      // data changes when clock goes from HIGH to LOW (since CKP is 0)
    SPI1CONbits.MSTEN = 1;    // master operation
    SPI1CONbits.ON = 1;       // turn on SPI1
    TRISBbits.TRISB15 = 0;
}


//where channel is 0 or 1 (for VoutA and VoutB), and voltage is the 8-bit output level.
void setVoltage(char channel, unsigned short voltage){
    int t = 0;
    unsigned char LSB,MSB;
    t = channel << 15;
    t = t | 0b0111000000000000;
    t = t | (voltage & 0b111111111111);
    LSB = t; 
    MSB = t >> 8; 
    CS = 0;                        // enable SPI1 by set chip select line low
    spi_io(MSB);
    spi_io(LSB);      
    CS = 1;                        // raise the chip select line, ending communication
}
