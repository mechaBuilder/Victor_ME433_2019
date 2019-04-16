/* 
 * File:   spi.h
 * Author: Victor Stepanov
 *
 * Created on April 16, 2019, 2:42 AM
 */

#ifndef SPI_H
#define	SPI_H

#define CS LATBbits.LATB15                      // chip select pin

void SPI_init();                                // initialize SPI
unsigned char spi_io(unsigned char o);          // send 1 byte via SPI, return response
void setVoltage(char channel, int voltage);     // set DAC channel & voltage 

#endif	/* SPI_H */

