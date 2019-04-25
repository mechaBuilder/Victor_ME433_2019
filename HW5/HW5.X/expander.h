#ifndef EXPANDER_H__
#define EXPANDER_H__
// Header file for expander.c file
// helps to implement MCP230008 I/O Expander

void initExpander();
void setExpander(char pin, char level);
char getExpander();


#endif