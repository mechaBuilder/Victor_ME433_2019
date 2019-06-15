#include <xc.h>
#include "motorControl.h"
#include<math.h>

//Left Motor:
    //DIR1 --> A10:     0 = forward
    //                  1 = back
    //OC1  --> B15     

//Right Motor:
    //DIR2 --> A7:      0 = forward
    //                  1 = back
    //OC4  --> A4


// functions
void PWM_init() {
    
    //RIGHT:
    
    //Turn on direction pin:
    TRISAbits.TRISA10 = 0;          
    LATAbits.LATA10 = 0;         //0: forward, 1: back. CHECKING ERROR
    
    //Remap pin B15 for OC1:
    RPB15Rbits.RPB15R = 0b0101;
    
    //Setup PWM & Timer 2:
    T3CONbits.TCKPS = 0;        // Timer2 prescaler N=1 (1:1)
    PR3 = 2399;                 // PR = PBCLK / N / desiredF - 1
    TMR3 = 0;                   // initial TMR2 count is 0
    OC1CONbits.OCM = 0b110;     // PWM mode without fault pin; other OC1CON bits are defaults
    OC1RS = 600;                // duty cycle = OC2RS/(PR2+1) = 25%
    OC1R = 0;                   // initialize before turning OC2 on; afterward it is read-only
    T3CONbits.ON = 1;           // turn on Timer2
    OC1CONbits.ON = 1;          // turn on OC1
    
     //LEFT:
    //Turn on direction pin:
    TRISAbits.TRISA7 = 0; 
    LATAbits.LATA7 = 0;
    
    //Remap A4 for OC4:
    RPA4Rbits.RPA4R = 0b0101;
    
    //Setup PWM & Timer 4:
    T4CONbits.TCKPS = 0;        // Timer4 prescaler N=1 (1:1)
    PR4 = 2399;                 // PR = PBCLK / N / desiredF - 1
    TMR4 = 0;                   // initial TMR4 count is 0
    OC4CONbits.OCM = 0b110;     // PWM mode without fault pin; other OC4CON bits are defaults
    OC4RS = 600;               // duty cycle = OC2RS/(PR2+1) = 25%
    OC4R = 0;                   // initialize before turning OC4 on; afterward it is read-only
    T4CONbits.ON = 1;           // turn on Timer4
    OC4CONbits.ON = 1;          // turn on OC4

}

unsigned short speedScaled(unsigned short speed) {
    unsigned short speedScaled = 24*speed;
    return speedScaled;
}

void rightWheel(unsigned short speed, unsigned short direction) {
    LATAbits.LATA10 = direction;
    OC1RS = speedScaled(speed);
}

void leftWheel(unsigned short speed, unsigned short direction) {
    LATAbits.LATA7 = direction;
    OC4RS = speedScaled(speed);
}

void forward(unsigned short speed){
    leftWheel(speed, FORWARD);
    rightWheel(speed,FORWARD);
}

void reverse(unsigned short speed){
    leftWheel(speed, REVERSE);
    rightWheel(speed,REVERSE);
}

void left(unsigned short speed) {
    leftWheel(speed, REVERSE);
    rightWheel(speed,FORWARD);
}

void right(unsigned short speed) {
    leftWheel(speed, FORWARD);
    rightWheel(speed,REVERSE);
}


void STOP(){
    OC1RS = 0;
    OC4RS = 0;
}

void PROPELLER(unsigned short speed, unsigned short direction){
    TRISBbits.TRISB3 = 0;       //Direction pin 
    LATBbits.LATB3 = direction; 
    
    //Using OC5 for PWM
    //Remap pin B2 for OC5:
    RPB2Rbits.RPB2R = 0b0110;
    
    //Setup PWM & Timer 2:
    T5CONbits.TCKPS = 0;        // Timer2 prescaler N=1 (1:1)
    PR5 = 2399;                 // PR = PBCLK / N / desiredF - 1
    TMR5 = 0;                   // initial TMR2 count is 0
    OC5CONbits.OCM = 0b110;     // PWM mode without fault pin; other OC1CON bits are defaults
    OC5RS = 0;//600;                // duty cycle = OC2RS/(PR2+1) = 25%
    OC5R = 0;                   // initialize before turning OC2 on; afterward it is read-only
    T5CONbits.ON = 1;           // turn on Timer2
    OC5CONbits.ON = 1;          // turn on OC1
    
    OC5RS = speedScaled(speed);
}




