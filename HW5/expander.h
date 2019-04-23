#ifndef EXPANDER_H__
#define EXPANDER_H__
// Header file for expander.c file
// helps to implement MCP230008 I/O Expander

SLAVE_ADDR_LED 0b1;
SLAVE_ADDR_PB  0b10000000; 

void initExpander();
void setExpander(char pin, char level);
char getExpander();


#endif