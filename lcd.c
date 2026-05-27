#include "lcd.h"

FILE lcdstream=FDEV_SETUP_STREAM(lcdputc, NULL, _FDEV_SETUP_WRITE);
void lcdinit(void)
{
	_delay_ms(45);
	LCD_DDR=0xFF;//ustawienie kierunklu na wyjsciowy
	lcd_write_instr(0x33);//wyslanie 2x 3
	lcd_write_instr(0x32);//ustawienie ze gadamy 4bitowo
	lcd_write_instr(0x28);//konfiguracja wyswietlacza 
	lcd_write_instr(0x08);//wylaczenie wyswietlacza
	lcd_write_instr(0x01);//wyczysc
	lcd_write_instr(0x06);//po wyslaniu znaku kurskor o 1 w prawo
	lcd_write_instr(0x0F);//wlaczenie wyswietlacza
	
}

void lcd_write_instr(uint8_t data)
{
	LCD_PORT&=~(1<<RS);//ustawiamy ze bedziemy wysylac instrukcje
	
	LCD_PORT|=(1<<E);
	LCD_PORT=(data&0xF0)|(LCD_PORT&0x0F);//zaslaniamy=MASKUJEMY nowe bity w data i stare bity w porcie
	_delay_ms(1);
	LCD_PORT&=~(1<<E);//zatrzasniecie 
	_delay_ms(1);
	
	LCD_PORT|=(1<<E);
	LCD_PORT=(data<<4)|(LCD_PORT&0x0F);//w data przesuwamy zeby miec tylko nowe bity i stare bity w porcie
	_delay_ms(1);
	LCD_PORT&=~(1<<E);//zatrzasniecie 
	_delay_ms(1);
	
}
void lcd_clear(void)
{
	lcd_write_instr(0x01);
}



void lcd_write_data(uint8_t data)
{
	LCD_PORT|=(1<<RS);//ustawiamy ze bedziemy wysylac dane 
	
	LCD_PORT|=(1<<E);
	LCD_PORT=(data&0xF0)|(LCD_PORT&0x0F);//zaslaniamy=MASKUJEMY nowe bity w data i stare bity w porcie
	_delay_ms(1);
	LCD_PORT&=~(1<<E);//zatrzasniecie 
	_delay_ms(1);
	
	LCD_PORT|=(1<<E);
	LCD_PORT=(data<<4)|(LCD_PORT&0x0F);//w data przesuwamy zeby miec tylko nowe bity i stare bity w porcie
	_delay_ms(1);
	LCD_PORT&=~(1<<E);//zatrzasniecie 
	_delay_ms(1);
}



void lcd_set_xy(uint8_t x, uint8_t y)
{
	lcd_write_instr(0x80+x+y*0x40);
}

void lcd_write_text_xy(uint8_t x, uint8_t y, char *text)
{
	lcd_set_xy(x,y);
	while(*text)
	{
		lcd_write_data(*text);
		text++;//prezesuniecie o 1
		}
	
}

	
void lcd_set_cursor(uint8_t B, uint8_t C) //lepiej by bylo na 2 zmiennych i 3 if
{
	
		if(B==0)//wylacz kursor
		{
			lcd_write_instr(0b00001100);
		}
		if(B==1&&C==0)//wlacz bez migania
		{
			lcd_write_instr(0b00001110);
		}
		if(B==1&&C==0)////wlacz kursor z miganiem
		{
			lcd_write_instr(0b00001111);
		}
	
	}
		
		
		
int lcdputc(char c,FILE *unused)
{
	lcd_write_data(c);
	return 0;
}
		
	
	
