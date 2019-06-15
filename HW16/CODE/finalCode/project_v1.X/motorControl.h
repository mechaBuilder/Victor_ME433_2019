#ifndef ILI9341_H__
#define ILI9341_H__

#define FORWARD 0
#define REVERSE 1 

// functions
void PWM_init();
unsigned short speedScaled(unsigned short speed);
void leftWheel(unsigned short speed, unsigned short direction);
void rightWheel(unsigned short speed, unsigned short direction);
void forward(unsigned short speed);
void reverse(unsigned short speed);
void left(unsigned short speed);
void right(unsigned short speed);
void STOP();
//void PROPELLER(unsigned short speed, unsigned short direction);


#endif