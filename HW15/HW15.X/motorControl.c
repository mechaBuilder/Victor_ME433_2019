#include <xc.h>
#include "motorControl.h"
#include<math.h>

// functions
void PWM_init() {
    //Turn on direction pin:
    TRISBbits.TRISB4 = 0; //pin 11
    LATBbits.LATB4 = 1;
    
    //Remap pin 14 for OC2:
    RPB5Rbits.RPB5R = 0b0101;
    
    //Setup PWM & Timer 2:
    T2CONbits.TCKPS = 0;        // Timer2 prescaler N=1 (1:1)
    PR2 = 2399;                 // PR = PBCLK / N / desiredF - 1
    TMR2 = 0;                   // initial TMR2 count is 0
    OC2CONbits.OCM = 0b110;     // PWM mode without fault pin; other OC1CON bits are defaults
    OC2RS = 600;               // duty cycle = OC2RS/(PR2+1) = 25%
    OC2R = 0;                   // initialize before turning OC2 on; afterward it is read-only
    T2CONbits.ON = 1;           // turn on Timer2
    OC2CONbits.ON = 1;          // turn on OC2

}

