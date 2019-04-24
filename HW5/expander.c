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

    i2c_master_start();                     // step 1, Begin the start sequence
	i2c_master_send(0x00 << 1);       		// step 2, send the slave address, left shifted by 1, 
                                            // which clears bit 0, indicating a write
	i2c_master_send(0b1);       			// step 3, send the slave address, left shifted by 1, 
    i2c_master_send(level);         		// step 4, message send a byte to the slave      - set it to high   

	i2c_master_stop();                      // send STOP:  end transmission, give up bus
 

	
	
}

char getExpander(); {
	//get input
    i2c_master_start();                     // step 1, Begin the start sequence

 	i2c_master_send(0x00 << 1);       		// step 2, send the slave address, left shifted by 1, 
                                            // which clears bit 0, indicating a write
	i2c_master_send(0b1);       			// step 3, send the slave address, left shifted by 1, 
	i2c_master_restart();                   // step 4, send a RESTART so we can begin reading 
	
	i2c_master_send(12<1|1); 				// write the address, shifted left by 1, or'ed with a 1 to indicate reading

	char r = i2c_master_recv(); 			// save the value returned

	i2c_master_ack(1); 						// make the ack so the slave knows we got it

	i2c_master_stop(); 						// make the stop bit
	

return r;
}
