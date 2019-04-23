#include "expander.c"
#include "i2c_master_noint.c"

#define SLAVE_ADDR 

void initExpander(); {

	ANSELBbits.ANSB2 = 0;
	ANSELBbits.ANSB3 = 0;
	
	//MCP23008
	//IPOL = 0b00000000;
	//GPINTEN = 0b00000000;
	//DEFVAL = 0b00000000;
	//INTCON = 
	//IOCON
	//GPPU
	//INTF
	//INTCAP
	//GPIO
	//OLAT 
	
	//IOCONbits.INTPOL = 0;
	//IOCONbits.ODR
	//IOCONbits.HAEN
	//IOCONbits.DISSLW
	IODIR = 0b11110000;
	IOCON.SEQOP = 1; 		// the MCP23X08 does not increment its address counter after each byte during the data transfer. 
}
void setExpander(char pin, char level); {
	//send output 

    i2c_master_start();                     // Begin the start sequence
	i2c_master_send(0x00 << 1);       		// send the slave address, left shifted by 1, 
                                            // which clears bit 0, indicating a write
	i2c_master_send(0b1);       			// send the slave address, left shifted by 1, 
    i2c_master_send(level);         			// send a byte to the slave      - set it to high   
    //i2c_master_send(master_write1);         // send another byte to the slave
	i2c_master_stop();                      // send STOP:  end transmission, give up bus
    i2c_master_restart();                   // send a RESTART so we can begin reading 

	
	
}

char getExpander(); {
	//get input
    i2c_master_start();                     // Begin the start sequence

    i2c_master_send((SLAVE_ADDR << 1) | 1); // send slave address, left shifted by 1,
                                            // and then a 1 in lsb, indicating read
    master_read0 = i2c_master_recv();       // receive a byte from the bus
    i2c_master_ack(0);                      // send ACK (0): master wants another byte!
    master_read1 = i2c_master_recv();       // receive another byte from the bus
    i2c_master_ack(1);                      // send NACK (1):  master needs no more bytes
    i2c_master_stop();                      // send STOP:  end transmission, give up bus

return 
}

