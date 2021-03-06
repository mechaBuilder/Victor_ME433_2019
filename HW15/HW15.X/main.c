#include<xc.h>           // processor SFR definitions
#include<sys/attribs.h>  // __ISR macro
#include "ili9341.h"
#include<stdio.h>
#include<string.h>
#include "motorControl.h" //PWM & direction pins

// DEVCFG0
#pragma config DEBUG = 0b11 // no debugging
#pragma config JTAGEN = 0b0 // no jtag
#pragma config ICESEL = 0b11 // use PGED1 and PGEC1
#pragma config PWP = 0x3f // no write protect
#pragma config BWP = 0b0 // no boot write protect
#pragma config CP = 0b1 // no code protect

// DEVCFG1
#pragma config FNOSC = 0b011 // use primary oscillator with pll
#pragma config FSOSCEN = 0b0 // turn off secondary oscillator
#pragma config IESO = 0b0 // no switching clocks
#pragma config POSCMOD = 0b10 // high speed crystal mode
#pragma config OSCIOFNC = 0b1 // disable secondary osc
#pragma config FPBDIV = 0b00 // divide sysclk freq by 1 for peripheral bus clock
#pragma config FCKSM = 0b11 // do not enable clock switch
#pragma config WDTPS = 0b10100 // use slowest wdt
#pragma config WINDIS = 0b1 // wdt no window mode
#pragma config FWDTEN = 0b0 // wdt disabled
#pragma config FWDTWINSZ = 0b11 // wdt window at 25%

// DEVCFG2 - get the sysclk clock to 48MHz from the 8MHz crystal
#pragma config FPLLIDIV = 0b001 // divide input clock to be in range 4-5MHz
#pragma config FPLLMUL = 0b111 // multiply clock after FPLLIDIV
#pragma config FPLLODIV = 0b001 // divide clock after FPLLMUL to get 48MHz
#pragma config UPLLIDIV = 0b001 // divider for the 8MHz input clock, then multiplied by 12 to get 48MHz for USB
#pragma config UPLLEN = 0b0 // USB clock on

// DEVCFG3
#pragma config USERID = 0b0 // some 16bit userid, doesn't matter what
#pragma config PMDL1WAY = 0b0 // allow multiple reconfigurations
#pragma config IOL1WAY = 0b0 // allow multiple reconfigurations
#pragma config FUSBIDIO = 0b1 // USB pins controlled by USB module
#pragma config FVBUSONIO = 0b1 // USB BUSON controlled by USB module

#define x  28
#define y  32

    unsigned short count = 0;

//Interrupt ISR:
void __ISR(12, IPL5SOFT) Timer3ISR(void) {          // step 1: ISR
                                            
    if (count <101) {
        count++;
        OC2RS = OC2RS + 24;
    }
    else {
        count = 0;
        OC2RS = 0;
        LATBINV = 0x10;                      //toggle B4
    }
    
    

    IFS0bits.T3IF = 0;                                          //clears the interrupt flag

// how many times has the interrupt occurred?

// set the duty cycle and direction pin

}

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
    //TRISBbits.TRISB4 = 1;
    //LATAbits.LATA4 = 1;
    
    //ANSELBbits.ANSB2 = 0;
	//ANSELBbits.ANSB3 = 0;
    
    //HW15 Interrupt: 
    PR3 = 59999;       // (PR3 + 1) x N x (1/48MHz) = (1/100Hz); sets the interrupt at 100 Hz
    TMR3 = 0;          // initialize count to zero
    T3CONbits.TCKPS = 0b011; // set prescaler N = 8 (1:8)
    T3CONbits.ON = 1;           // turn on Timer 3
    IPC3bits.T3IP = 5;          //interupt priority
    IFS0bits.T3IF = 0;          //clear flag
    IEC0bits.T3IE = 1;          //enable interrupt
    __builtin_enable_interrupts();
    

    SPI1_init();
    LCD_init();
    LCD_clearScreen(ILI9341_PURPLE);
    
    //HW15:
    PWM_init();

    char message[100];


    while(1) {
        //Heartbeat
        _CP0_SET_COUNT(0);
        while(_CP0_GET_COUNT() < 4800000) {
            LATAbits.LATA4 = 0;
        }
        _CP0_SET_COUNT(0);
        while(_CP0_GET_COUNT() < 4800000) {
            LATAbits.LATA4 = 1;
        }
        sprintf(message, "HW 15: motorControl");
        print2LCD(message, x, y+100, ILI9341_WHITE, ILI9341_PURPLE);
        
        sprintf(message, "count = %d", count);
        print2LCD(message, x, y+110, ILI9341_WHITE, ILI9341_PURPLE);
        
        //Camera function to print a row of pixels:
        LCDprintRow(0, 0);
        
    }
}