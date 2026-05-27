#include <avr/io.h>
#include <util/delay.h>
#include "lcd.h"
#include "USART.h"
#include "morse.h"
#include <string.h>

volatile uint8_t i;
volatile  char znak;
volatile char bufor[20];
volatile char signal[20];



char morse_signal[30];
volatile char decoded_signal[30];
volatile uint8_t idx_bufor;
volatile uint16_t T_nacisniecia=0;
volatile uint16_t T_pauzy=0;
volatile uint16_t t=0;
volatile uint8_t wczesniej_wcisniety;



//przerwanie licznika 1
ISR(TIMER1_COMPA_vect)
{
	t++;
	
	if(!(PIND&(1<<0)))//czy wcisniety teraz
	{
		if(wczesniej_wcisniety==0)
		{
			T_pauzy=0;
			T_nacisniecia=0;
			wczesniej_wcisniety=1;//teraz jest wcisniety a wczesniej nie byl to zmiana flagi jakby
			
		}
		//jak teraz wcisniety i wczesniej wcisniety to
		else
		{
		T_nacisniecia++;
		}
	}
	else //teraz niewcisniety
	{
		if(wczesniej_wcisniety==1)
		{
			if(T_nacisniecia<300)
			{
				//'.'
				morse_signal[idx_bufor]='.';
				idx_bufor++;
				morse_signal[idx_bufor]='\0';//sygnal konca 
				
			}
			else
			{
				//'-'
				morse_signal[idx_bufor]='-';
				idx_bufor++;
				morse_signal[idx_bufor]='\0';//sygnal konca 
			}
			T_pauzy=0;
			T_nacisniecia=0;
			wczesniej_wcisniety=0;//zmiana flagi
		}
		//jak teraz niewcisniety i wczesniej niewcisniety to
		else
		{ 
			T_pauzy++;
			
			if (T_pauzy >= 1000&&idx_bufor>0) 
			{ 
				//dekoduj
                char litera[2] = {0};
                litera[0] = decode((char*)morse_signal); 
                
                if(litera[0] != 0)
                {
                    strcat((char*)decoded_signal, litera);
                    strcat((char*)decoded_signal, " ");
                }
                morse_signal[0] = '\0'; 
                idx_bufor = 0;
            
			//wyswietl
			lcd_clear();
			lcd_set_xy(0,0); 
			fprintf(&lcdstream,decoded_signal);
			lcd_set_cursor(0,0);
		}
			
		}
	}

	
	
	
}
  
ISR(USART_RXC_vect)//przerwanie na usart
{
	
	znak=UDR; //odczytujemy, zwalniamy rejestr, bo usart recieve ma petle co zawiesza
	bufor[i]=znak;
	i++;
	if(znak=='\n')
	{
		signal[0] = '\0';//wyczyszczenie signal
		
		for(int j=0; j <(i-1); j++)//wczytywanie znak po znaku
        {
            strcat(signal, code(bufor[j]));
            strcat(signal, " ");    
              
        }

		lcd_clear();
		lcd_set_xy(0,0); 
		fprintf(&lcdstream,signal);
		lcd_set_cursor(0,0);
			
		fprintf(&ustream,signal);
		fprintf(&ustream,"\n");
		
		signal2LED(signal);
		i=0;
	}

		
}




int main (void)
{
	
	DDRB=0xFF; //dioda 
	
	USART_Init(1);
	fprintf(&ustream,"\n wpisz slowo ktore chcesz zakodowac \n ");
	lcdinit();
	

	lcd_set_xy(0,0);
	
	
	DDRD=0x00;//wszytsko na wejscie 
	PORTD=0xFF; //rezystory podciagajace 
	PORTC=0b00000001;
	
	//timer ;c
	TCCR1B|=(1<<WGM12);//tryb pracy licznika ctc licznika 1
	TIMSK|=(1<<OCIE1A);//przerwanie licznika 1 przy porownaniu 
	OCR1A=249;//OCR1A=16000000/nasza czestotliwosc/preskaler(N) -1 =>1000Hz, jak 0,001s to 15
	TCCR1B|=(1<<CS10)|(1<<CS11);//preskaler N=64
	
	sei();
	
	

	while(1)
	{
		
		
	}
	
	return 0; 
}


