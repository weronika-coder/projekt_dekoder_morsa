#include "morse.h"


char* code(char znak)
{
	if(znak=='a')
	{
		return ".-";
		
	}
	
	if(znak=='b')
	{
		return "-...";
		
	}
	if(znak=='c')
	{
		return "-.-.";
		
	}
	if(znak=='d')
	{
		return "-..";
		
	}
	if(znak=='e')
	{
		return ".";
		
	}
	if(znak=='f')
	{
		return "..-.";
		
	}
	if(znak=='g')
	{
		return "--.";
		
	}
	if(znak=='h')
	{
		return "....";
		
	}
	if(znak=='i')
	{
		return "..";
		
	}
	if(znak=='j')
	{
		return ".---";
		
	}
	if(znak=='k')
	{
		return "-.-";
		
	}
	if(znak=='l')
	{
		return ".-..";
		
	}
	if(znak=='m')
	{
		return "--";
		
	}
	if(znak=='n')
	{
		return "-.";
		
	}
	if(znak=='o')
	{
		return "---";
		
	}
	if(znak=='p')
	{
		return ".--.";
		
	}
	if(znak=='q')
	{
		return "--.-";
		
	}
	if(znak=='r')
	{
		return ".-.";
		
	}
	if(znak=='s')
	{
		return "...";
		
	}
	if(znak=='t')
	{
		return "-";
		
	}
	if(znak=='u')
	{
		return "..-";
		
	}
	if(znak=='v')
	{
		return "...-";
		
	}
	if(znak=='w')
	{
		return ".--";
		
	}
	if(znak=='x')
	{
		return "-..-";
		
	}
	if(znak=='y')
	{
		return "-.--";
		
	}
	if(znak=='z')
	{
		return "--..";
		
	}
	return 0;
	

	
}





void signal2LED(char* signal)
{
	int len = strlen(signal); 
    for(int i = 0; i < len; i++)
    {
        PORTB = 0xFF; 
        if(signal[i] == '.') 
        {
            _delay_ms(100);
        } 
        else if(signal[i] == '-') 
        {
            _delay_ms(1000);
        }
        PORTB = 0x00; 
        _delay_ms(150); 
    }

}





char decode(char* signal)
{
	if(strcmp(signal,".-")==0)
	{
		return 'a';
		
	}
	
	if(strcmp(signal,"-...")==0)
	{
		return 'b';
		
	}
	if(strcmp(signal,"-.-.")==0)
	{
		return 'c';
		
	}
	if(strcmp(signal,"-..")==0)
	{
		return 'd';
		
	}

	if(strcmp(signal,".")==0)
	{
		return 'e';
		
	}
	
	
	if(strcmp(signal,"..-.")==0)
	{
		return 'f';
		
	}
	
	if(strcmp(signal,"--.")==0)
	{
		return 'g';
		
	}
	
	if(strcmp(signal,"....")==0)
	{
		return 'h';
		
	}
	if(strcmp(signal,"..")==0)
	{
		return 'i';
		
	}
	if(strcmp(signal,".---")==0)
	{
		return 'j';
		
	}
	
	if(strcmp(signal,"-.-")==0)
	{
		return 'k';
		
	}
	
	if(strcmp(signal,".-..")==0)
	{
		return 'l';
		
	}
	if(strcmp(signal,"--")==0)
	{
		return 'm';
		
	}
	if(strcmp(signal,"-.")==0)
	{
		return 'n';
		
	}
	if(strcmp(signal,"---")==0)
	{
		return 'o';
		
	}
	if(strcmp(signal,".--.")==0)
	{
		return 'p';
		
	}
	if(strcmp(signal,"--.-")==0)
	{
		return 'q';
		
	}
	if(strcmp(signal,".-.")==0)
	{
		return 'r';
		
	}
	if(strcmp(signal,"...")==0)
	{
		return 's';
		
	}
	if(strcmp(signal,"-")==0)
	{
		return 't';
		
	}
	if(strcmp(signal,"..-")==0)
	{
		return 'u';
		
	}
	if(strcmp(signal,"...-")==0)
	{
		return 'v';
		
	}
	if(strcmp(signal,".--")==0)
	{
		return 'w';
		
	}
	if(strcmp(signal,"-..-")==0)
	{
		return 'x';
		
	}
	if(strcmp(signal,"-.--")==0)
	{
		return 'y';
		
	}
	if(strcmp(signal,"--..")==0)
	{
		return 'z';
		
	}
	return 0;
}
