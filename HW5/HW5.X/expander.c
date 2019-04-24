#include "expander.h"
#include "i2c_master_noint.h"

#define LED_ADDR 0b00000001 //A0 GP0 (pin 10)
#define PB_ADDR 0b10000000  //A7 GP7 (pin 17)
#define OP_ADDR 0b01000000  // Device Iptocode
#define A0 0b00000001
#define A1 0b00000010
#define A2 0b00000100
#define A3 0b00001000
#define A4 0b00010000
#define A5 0b00100000
#define A6 0b01000000
#define A7 0b10000000
#define SLAVE_ADDR 0x20  //0b 010 0000

void initExpander() {

    i2c_master_setup();
    i2c_master_start();                     // make the start bit
    i2c_master_send(SLAVE_ADDR<<1|0);       // 0 indicate writing
    i2c_master_send(0x00);                  // write to IODIR
    i2c_master_send(0xF0);                  // GP7-GP4:read; GP3-GP0:write
    i2c_master_stop();                      // make the stop bit
}
void setExpander(char pin, char level) {
	//output 
    i2c_master_start();                     // Begin the start sequence
    i2c_master_send(SLAVE_ADDR<<1|0);       // 0 indicate writing
    i2c_master_send(0x0A);                  // write to OLAT
    i2c_master_send(level<<pin);            // the value to put in the register
    i2c_master_stop();                      // send a RESTART so we can begin reading 
}

char getExpander() {
    //input
    char input;
    i2c_master_start();                     // Begin the start sequence
    i2c_master_send(SLAVE_ADDR<<1|0);       // 0 indicate writing
    i2c_master_send(0x09);                  // write to GPIO
    //i2c_master_send(0x7);                  // write to GPIO
    //i2c_master_send(0x00);                  // the value to put in the register
    //i2c_master_stop();                      // send a RESTART so we can begin reading 
    
    i2c_master_restart();                   // send a RESTART so we can begin reading
    //i2c_master_start();                     // Begin the start sequence
    i2c_master_send((SLAVE_ADDR << 1) | 1); // send slave address, left shifted by 1,
                                            // and then a 1 in lsb, indicating read
    input = i2c_master_recv();       // receive a byte from the bus
    //i2c_master_ack(0);                      // send ACK (0): master wants another byte!
    //master_read1 = i2c_master_recv();       // receive another byte from the bus
    i2c_master_ack(1);                      // send NACK (1):  master needs no more bytes
    i2c_master_stop();                      // send STOP:  end transmission, give up bus
    return input;
}

