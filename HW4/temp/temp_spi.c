// initialize SPI1 and the ram module
void SPI_init() {
  // set up the chip select pin as an output
  // the chip select pin is used by the sram to indicate
  // when a command is beginning (clear CS to low) and when it
  // is ending (set CS high)
 TRISBbits.TRISB15 = 0;
 CS = 1;

  // Master - SPI1, pins are: SDI1(B11), SDO1(B13), SCK1(B14).  
  // we manually control SS1 as a digital output (B15)
  // since the pic is just starting, we know that spi is off. We rely on defaults here
 
  RPB13Rbits.RPB13R = 0b0011; // Set SDO1 to B13
  SDI1Rbits.SDI1R = 0b0011; // Set SDI1 to B8, actually not connected to DAC
  SPI1CON = 0;              // turn off the spi module and reset it
  SPI1BUF;                  // clear the rx buffer by reading from it
  SPI1BRG = 0x1;            // baud rate to 12 MHz [SPI1BRG = (48000000/(2*desired))-1]
  SPI1STATbits.SPIROV = 0;  // clear the overflow bit
  SPI1CONbits.CKE = 1;      // data changes when clock goes from hi to lo (since CKP is 0)
  SPI1CONbits.MSTEN = 1;    // master operation
  SPI1CONbits.ON = 1;       // turn on spi 1
}

// send a byte via spi and return the response
unsigned char spi_io(unsigned char o) {
  SPI4BUF = o;
  while(!SPI4STATbits.SPIRBF) { // wait to receive the byte
    ;
  }
  return SPI4BUF;
}

void setVoltage(char channel, int voltage) {
	unsigned short t = 0;
    unsigned char MSB, LSB;
    //voltage = voltage & 0b111111111111;
	t= channel << 15; //channel is at the very end of the data transfer //the most significant bit
	t = t | 0b0111000000000000; //16-bit word. bits <15:12> are configuration bits for DAC
	t = t | (voltage & 0b111111111111); //convert v into binary from decimal
    MSB = t >> 8;
    LSB = t & 0b0000000011111111;
	
	CS = 0;                     // enable data transfer
	spi_io(MSB);
	spi_io(LSB);
    CS = 1;                     // disable data transfer 
}
