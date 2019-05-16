#include<xc.h>           // processor SFR definitions
#include<sys/attribs.h>  // __ISR macro
#include "ili9341.h"
#include<stdio.h>
#include<string.h>
#include "i2c_master_noint.h"
#include "imu.h"

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
    LATAbits.LATA4 = 1;
    
    ANSELBbits.ANSB2 = 0;
	ANSELBbits.ANSB3 = 0;

    __builtin_enable_interrupts();
    

    SPI1_init();
    LCD_init();
    imu_init();
    LCD_clearScreen(ILI9341_PURPLE);
    char message[100];
    unsigned char data[LENGTH]; //14
    signed short aX, aY, aZraw;
    
    signed short buffer[3]={0,0,0,0};
    signed short buffer_y[3]={0,0,0,0};
    
    float IIR4 = 0.0;
    float A1=-0.0013, A2=0.0264, A3=0.1558, A4=0.3192, B1=0.3192, B2=0.1558, B3=0.0264, B4=-0.0013;
    
    while(1) {
        //Read LCM at 20 Hz
        LATAbits.LATA4 = 0;
        _CP0_SET_COUNT(0);
        while (_CP0_GET_COUNT()<=1200000){;} //delay
        LATAbits.LATA4 = 1;
        
        //WHO AM I
        signed char input = whoAmI();
        sprintf(message, "Who Am I = %d (105)", input);
        print2LCD(message, x, y, ILI9341_WHITE, ILI9341_PURPLE);
        
        //Let's get some readings from IMU
        I2C_read_multiple(SLAVE_ADDR, OUT_TEMP_L, data, LENGTH);
        //aX = (data[9]  << 8) | data[8];
        //aY = (data[11] << 8) | data[10];
        aZraw = (data[13] << 8) | data[11];
        sprintf(message, "aZraw = %d  ", aZraw);
        print2LCD(message, x, y+20, ILI9341_WHITE, ILI9341_PURPLE);
        
        //HW11 create a buffer:

        float MAF4;
        float FIR4, a1=0.0350, a2=0.4650, a3=0.4650, a4=0.0350; //0.0350    0.4650    0.4650    0.0350
        //for (i=3;i<=1;i--){
         //   buffer[i]=buffer[i-1];
        //        }
        buffer[3]=buffer[2];
        buffer[2]=buffer[1];
        buffer[1]=buffer[0];
        buffer[0]=aZraw;
        
        //output for IIR:
        buffer_y[3] = buffer_y[2];
        buffer_y[2] = buffer_y[1];
        buffer_y[1] = buffer_y[0];
        buffer_y[0] = IIR4;
        
        sprintf(message, "buffer[0] = %d  ", buffer[0]);
        print2LCD(message, x, y+100, ILI9341_WHITE, ILI9341_PURPLE);
        sprintf(message, "buffer[1] = %d  ", buffer[1]);
        print2LCD(message, x, y+110, ILI9341_WHITE, ILI9341_PURPLE);
        sprintf(message, "buffer[2] = %d  ", buffer[2]);
        print2LCD(message, x, y+120, ILI9341_WHITE, ILI9341_PURPLE);
        sprintf(message, "buffer[3] = %d  ", buffer[3]);
        print2LCD(message, x, y+130, ILI9341_WHITE, ILI9341_PURPLE);
        
        
        MAF4 = (buffer[0]+buffer[1]+buffer[2]+buffer[3])/4.0;
                sprintf(message, "MAF4 = %.2f  ", MAF4);
        print2LCD(message, x, y+40, ILI9341_WHITE, ILI9341_PURPLE);
        
        FIR4 = a1*buffer[0]+ a2*buffer[1]+ a3*buffer[2]+a4*buffer[3];
                sprintf(message, "FIR4 = %.2f  ", FIR4);
        print2LCD(message, x, y+50, ILI9341_WHITE, ILI9341_PURPLE);
        
        IIR4 = A1*buffer[0]+ A2*buffer[1]+ A3*buffer[2]+A4*buffer[3]+B1*buffer_y[0]+B2*buffer_y[1]+B3*buffer_y[2]+B4*buffer_y[3];
        sprintf(message, "IIR4 = %.2f  ", IIR4);
        print2LCD(message, x, y+60, ILI9341_WHITE, ILI9341_PURPLE);
        
        
        
        
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