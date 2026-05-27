#include "USART.h"

FILE ustream=FDEV_SETUP_STREAM(uputc, NULL, _FDEV_SETUP_WRITE);
void USART_Init( unsigned int baud )
{
	/* prę dkoś ć transmisji */
	UBRRH = (unsigned char)(baud>>8);
	UBRRL = (unsigned char)baud;
	
	
	UCSRC = (1<<URSEL)|(1<<USBS)|(3<<UCSZ0);/* Format ramki: słowo=8bitów, 2 bity stopu */
	UCSRB = (1<<RXEN)|(1<<TXEN); /* Włączenie odbiornika i nadajnika */
	UCSRB|=(1<<RXCIE);//wlaczenie przerwania gdy przyszla dana
}


void USART_Transmit( unsigned char data )
{
	/* Czekaj, aż zwolni się bufor nadajnika */
	while ( !( UCSRA & (1<<UDRE)) );
	/* Umieś ć daną w buforze i ją wyś lij */
	UDR = data;
}

unsigned char USART_Receive( void )
{
	/* Czekaj, aż pojawi się dana do odbioru */
	while ( !(UCSRA & (1<<RXC)) ) ;
	/* Odbierz daną */
	return UDR;
}

		
int uputc(char c,FILE *unused)
{
	USART_Transmit(c);
	return 0;
}
		
	
