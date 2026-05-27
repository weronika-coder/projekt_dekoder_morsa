#pragma once
#include <avr/io.h>
#include <stdio.h>
#include <avr/interrupt.h>

extern FILE ustream;

void USART_Init( unsigned int baud );
void USART_Transmit( unsigned char data );
unsigned char USART_Receive( void );
int uputc(char c,FILE *unused);
