#ifndef _morse_h
#define _morse_h
//DYREKTYWY KOMPILACJI WARUNKOWEJ 
#include <util/delay.h>
#include <avr/io.h> 
#include <string.h>
 
char* code(char znak); //definicja funkcji 
void signal2LED(char* signal);
char decode(char* signal); 


#endif
