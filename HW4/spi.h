#ifndef SPI__H__
#define SPI__H__

#include <xc.h>           // processor SFR definitions
#include <sys/attribs.h>  // __ISR macro

// Demonstrates spi by accessing external ram
// PIC is the master, ram is the slave
// Uses microchip MCP4922 12 bit
// SDO1 -> SI (pin B13 (pin 24) -> pin 5)
// SDI1 -> SO (pin B11 (pin 22)  -> /)(we donot use it)
// SCK1 -> SCK (pin B14 (pin 25) -> pin 4)
// SS1 -> CS (pin B15 (pin 26) -> pin 3)
// Additional MCP4912 connections
// Vdd (Pin 1), VrefA(13), VrefB(11) -> 3.3V
// LDAC (Pin 8), Vss (Pin 12) -> ground
// VoutA(14), VoutB(10) -> output 
#define CS LATBbits.LATB15                // chip select pin
#define OUTA 0         
#define OUTB 1
#define PI 3.1415926535898

unsigned char spi_io(unsigned char ch); // send a byte via spi and return the response
void SPI_init(); // initialize SPI1
void setVoltage(char channel, unsigned short voltage); // set channel and voltage
    
#endif