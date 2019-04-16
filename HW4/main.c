/* 
 * File:   main.c
 * Author: Victor Stepanov
 *
 * Created on April 16, 2019, 2:41 AM
 */

#include <xc.h>             // processor SFR definitions
#include <sys/attribs.h>    // __ISR macro
//#include "NU32.h"           // constants, funcs for startup and UART
#include <math.h>           //for sine wave plotting
#include "spi.h"
// Demonstrates SPI by accessing external DAC
// PIC is the master, DAC is the slave
// Uses microchip 4922 DAC (see the data sheet for protocol details)
// SDO1 -> SDI (pin B13 (24) -> pin 5)
// SDI1 -> SDO (pin B11 (22) -> not used)
// SCK1 -> SCK (pin B14 (25) -> pin 4)
// SS1  -> CS  (pin B15 (26) -> pin 3)
// Additional DAC connections:
// Vss (Pin 12)   -> ground
// Vdd (Pin 1)    -> 3.3 V
// VRefA (Pin 13) -> 3.3V
// VRefB (Pin 11) -> 3.3V 

// DEVCFG0
#pragma config DEBUG = 11 // no debugging
#pragma config JTAGEN = 0 // no jtag
#pragma config ICESEL = 11 // use PGED1 and PGEC1
#pragma config PWP = 111111111 // no write protect
#pragma config BWP = 0 // no boot write protect
#pragma config CP = 1 // no code protect

// DEVCFG1
#pragma config FNOSC = 011 // use primary oscillator with pll
#pragma config FSOSCEN = 0 // turn off secondary oscillator
#pragma config IESO = 0 // no switching clocks
#pragma config POSCMOD = 10 // high speed crystal mode
#pragma config OSCIOFNC = 1 // disable secondary osc
#pragma config FPBDIV = 00 // divide sysclk freq by 1 for peripheral bus clock
#pragma config FCKSM = 11 // do not enable clock switch
#pragma config WDTPS = 10100 // use slowest wdt
#pragma config WINDIS = 1 // wdt no window mode
#pragma config FWDTEN = 0 // wdt disabled
#pragma config FWDTWINSZ = 11 // wdt window at 25%

// DEVCFG2 - get the sysclk clock to 48MHz from the 8MHz crystal
#pragma config FPLLIDIV = 001 // divide input clock to be in range 4-5MHz
#pragma config FPLLMUL = 111 // multiply clock after FPLLIDIV
#pragma config FPLLODIV = 001 // divide clock after FPLLMUL to get 48MHz
#pragma config UPLLIDIV = 001 // divider for the 8MHz input clock, then multiplied by 12 to get 48MHz for USB
#pragma config UPLLEN = 0 // USB clock on

// DEVCFG3
#pragma config USERID = 0 // some 16bit userid, doesn't matter what
#pragma config PMDL1WAY = 0 // allow multiple reconfigurations
#pragma config IOL1WAY = 0 // allow multiple reconfigurations
#pragma config FUSBIDIO = 1 // USB pins controlled by USB module
#pragma config FVBUSONIO = 1 // USB BUSON controlled by USB module

int main(void) {
  void SPI_init();
  while(1) {
	_CPO_SET_COUNT(0);
	float f = 512 +512*sin(i*2*3.1415/1000*10);  //should make a 10Hz sin wave)
	i++;

	setVoltage(0,512);		//test
	setVoltage(1,256);		//test

	while(_CPO_GET_COUNT() < 2400000000/1000) {}  //check this is 24Million
    ;
  }
  return 0;
}
