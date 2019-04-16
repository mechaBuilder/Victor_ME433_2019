#ifndef SPI_H
#define	SPI_H

#define CS LATAbits.LATB15       // chip select pin

void SPI_init();
unsigned char spi_io(unsigned char o);
void setVoltage(char channel, int voltage);

#endif	/* SPI_H */

