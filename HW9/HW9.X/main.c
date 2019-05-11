#include<xc.h>           // processor SFR definitions
#include<sys/attribs.h>  // __ISR macro
#include "ili9341.h"
#include<stdio.h>
#include<string.h>
//#include "i2c_master_noint.h"
//#include "imu.h"

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

#define x  28
#define y  32
#define c1 ILI9341_WHITE
#define c2 ILI9341_PURPLE
#define c3 ILI9341_DARKGREEN
#define c4 ILI9341_YELLOW
#define c5 ILI9341_RED

#define LENGTH 14

#define x0 120
#define y0 160
#define xP 200
#define xM 20
#define yP 240
#define yM 80


//#define OUT_TEMP_L 0x20

int main() {

    __builtin_disable_interrupts();

    // set the CP0 CONFIG register to indicate that kseg0 is cacheable (0x3)
    __builtin_mtc0(_CP0_CONFIG, _CP0_CONFIG_SELECT, 0xa4210583);

    // 0 data RAM access wait states
    BMXCONbits.BMXWSDRM = 0x0;

    // enable multi vector interrupts
    INTCONbits.MVEC = 0x1;

    // disable JTAG to get pins back
    DDPCONbits.JTAGEN = 0;

    // do your TRIS and LAT commands here
    TRISAbits.TRISA4 = 0;
    TRISBbits.TRISB4 = 1;
    //LATAbits.LATA4 = 1;
    
    ANSELBbits.ANSB2 = 0;
	ANSELBbits.ANSB3 = 0;

    __builtin_enable_interrupts();
    

    SPI1_init();
    SPI2_init();
    LCD_init();
    //imu_init();
    LCD_clearScreen(c2);
    char message[100];
    //unsigned char data[LENGTH]; //14
    //signed short aX, aY;
    while(1) {
        //Read LCM at 20 Hz
        LATAbits.LATA4 = 0;
        _CP0_SET_COUNT(0);
        while (_CP0_GET_COUNT()<=1200000){ //delay
        LATAbits.LATA4 = 1;
        }
//        //WHO AM I
//        signed char input = whoAmI();
        sprintf(message, "Hello World");
        print2LCD(message, x, y, c1, c2);
        unsigned short Xpos, Ypos, xtemp, ytemp, ztemp; 
        int z; 
        XPT2046_read(&Xpos, &Ypos, &z);
        sprintf(message, "val1 = %d", Xpos);
        print2LCD(message, x, y+20, c1, c2);
        sprintf(message, "val2 = %d", Ypos);
        print2LCD(message, x, y+30, c1, c2);
        sprintf(message, "val3 = %d", z);
        print2LCD(message, x, y+40, c1, c2);
        //Xpos = xtemp; //*Ypos = ytemp; *z = ztemp;
        //unsigned short Xpos_actual = (xtemp >> 1) <<3;
        //sprintf(message, "Xpos = %d", Xpos_actual);
        //print2LCD(message, x, y+20, c1, c2);
//        
//        //Let's get some readings from IMU
//        I2C_read_multiple(SLAVE_ADDR, OUT_TEMP_L, data, LENGTH);
//        aX = (data[9]  << 8) | data[8];
//        aY = (data[11] << 8) | data[10];
//        sprintf(message, "aX = %d  ", aX);
//        print2LCD(message, x, y+10, c1, c2);
//        sprintf(message, "aY = %d  ", aY);
//        print2LCD(message, x, y+20, c1, c2);
//        signed char aXscaled = ((int)aX/165.0);
//        signed char aYscaled = ((int)aY/165.0);
//        sprintf(message, "aXscaled = %d  ", aXscaled);
//        print2LCD(message, x, y+40, c5, c2);
//        sprintf(message, "aYscaled = %d  ", aYscaled);
//        print2LCD(message, x, y+50, c5, c2);
//
//        //Let's draw bars:
//        barX(x0, y0, 100, aXscaled, c3, c5);
//        barY(x0, y0, 100, aYscaled, c3, c5);
    }
}