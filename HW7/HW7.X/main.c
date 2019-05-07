#include<xc.h>           // processor SFR definitions
#include<sys/attribs.h>  // __ISR macro
#include "ili9341.h"
#include<stdio.h>
#include<string.h>
#include "i2c_master_noint.h"
#include "imu.h"

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
    LATAbits.LATA4 = 1;
    
    ANSELBbits.ANSB2 = 0;
	ANSELBbits.ANSB3 = 0;

    __builtin_enable_interrupts();
    

    SPI1_init();
    LCD_init();
    imu_init();
    LCD_clearScreen(c2);
    char message[100];
    unsigned short update, bar_size = 100;
    double FPS = 0.0, count = 0.0; 
    
    unsigned char data[LENGTH]; //14
    signed short temp, gyroX, gyroY, gyroZ, accelX, accelY, accelZ;
    
    
    int input = 0;
    
    while(1) {
        //Read LCM at 20 Hz
        LATAbits.LATA4 = 0;
        _CP0_SET_COUNT(0);
        while (_CP0_GET_COUNT()<=1200000){;}
        LATAbits.LATA4 = 1;
        //WHO AM I
        input = whoAmI();
        sprintf(message, "Who Am I = %d (105)", input);
        print2LCD(message, x, y, c1, c2);
        //Let's get some readings from IMU
        I2C_read_multiple(SLAVE_ADDR, OUT_TEMP_L, data, LENGTH);
        accelX = (data[9]  << 8) | data[8];
        accelY = (data[11] << 8) | data[10];
        sprintf(message, "accelX = %d  ", accelX);
        print2LCD(message, x, y+10, c1, c2);
        sprintf(message, "accelY = %d  ", accelY);
        print2LCD(message, x, y+20, c1, c2);
        int aX = ((int)accelX/165.0);
        int aY = ((int)accelY/165.0);
        sprintf(message, "aX = %d  ", aX);
        print2LCD(message, x, y+40, c1, c2);
        int aXpos = abs(aX);
        sprintf(message, "aXpos = %d  ", aXpos);
        print2LCD(message, x, y+50, c1, c2);
        
        barX(x0, y0, 100, aX, c3, c5);
        barY(x0, y0, 100, aY, c3, c5);
        
//        if (aX>=0) {
//            //X+ direction
//            if (update<=aX) {
//                while (update<=aX) {
//                    progressBarX_pos(x0,y0,100,update, c3,c5);
//                    update++;
//                }
//            }
//            else if (update>aX) {
//                while (update>aX) {
//                    progressBarX_pos(x0,y0,100,update, c3,c5);
//                    update--;
//                }
//            }
//            else {;}
//        }
//        else {
//            //X- direction
//            if (update>=aX) {
//                while (update>=aX) {
//                    progressBarX_neg(x0,y0,100,update, c3,c5);
//                    update--;
//                }
//            }
//            else if (update<aX) {
//                while (update<aX) {
//                    progressBarX_neg(x0,y0,100,update, c3,c5);
//                    update++;
//                }
//            }
//            else {;}
//        }
            
    
        
//        update = 0;
//         
//        while (update <= bar_size) {
//            _CP0_SET_COUNT(0);
//            sprintf(message,"Hello world %d %% ", update);
//            print2LCD(message, x, y, c1, c2);
//            progressBar(x,y+20,bar_size,update, c3,c4);
//            while (_CP0_GET_COUNT()<=2400000){;}
//            count=_CP0_GET_COUNT();
//            FPS=1.00/(count/24000000.0);
//            sprintf(message, "FPS = %.2f", FPS);
//            print2LCD(message, x, y+30, c3, c2);
//            update++;
//            
//
//            
//            
//        }
                    



            //temp   = (data[1]  << 8) | data[0];
            //gyroX  = (data[3]  << 8) | data[2];
            //gyroY  = (data[5]  << 8) | data[4];
            //gyroZ  = (data[7]  << 8) | data[6];
        //accelX = (data[9]  << 8) | data[8];
        //accelY = (data[11] << 8) | data[10];
            //accelZ = (data[13] << 8) | data[12];
            //gyroX, gyroY, gyroZ, accelX, accelY, accelZ;
            
            //unsigned short val = data[12];
            //sprintf(message, "temp = %d  ", temp);
            //print2LCD(message, x, y+60, c1, c5);
            
            //sprintf(message, "gyroX = %d  ", gyroX);
            //print2LCD(message, x, y+70, c1, c5);
            //sprintf(message, "gyroY = %d  ", gyroY);
            //print2LCD(message, x, y+80, c1, c5);
            //sprintf(message, "gyroZ = %d  ", gyroZ);
            //print2LCD(message, x, y+90, c1, c5);
            
//        sprintf(message, "accelX = %d  ", accelX);
//        print2LCD(message, x, y+100, c1, c5);
//        sprintf(message, "accelY = %d  ", accelY);
//        print2LCD(message, x, y+110, c1, c5);
            //sprintf(message, "accelZ = %d  ", accelZ);
            //print2LCD(message, x, y+120, c1, c5);
            
        
	// use _CP0_SET_COUNT(0) and _CP0_GET_COUNT() to test the PIC timing
	// remember the core timer runs at half the sysclk
//        if (!PORTBbits.RB4) {
//            LATAbits.LATA4 = 0;
//        }
//        else {
//            _CP0_SET_COUNT(0);
//            while(_CP0_GET_COUNT() < 4800000) {
//                LATAbits.LATA4 = 0;
//            }
//            _CP0_SET_COUNT(0);
//            while(_CP0_GET_COUNT() < 4800000) {
//                LATAbits.LATA4 = 1;
//            }
//        }
    
    }
}