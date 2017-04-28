#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/sfr_defs.h>
#include <stdio.h>

void uart_print(char *str);
void uart_print(char *str)
{
	while(*str)
	{
		UDR = *str; str++;
		while(bit_is_clear(UCSRA, UDRE)){};
	}
	UDR = '\n';
	while(bit_is_clear(UCSRA, UDRE)){};
	
}
int main() {
	//khoi tao UART 9600 UBRRL = 103
	
	char tem[20];
	static unsigned int n=0;
	
	DDRB |= 0xFF; // all is output
	UBRRH=0;
	UBRRL=103;
	//cho phep truyen
	UCSRA=0;
	
	UCSRC=(1<<URSEL)|(1<<UCSZ0)|(1<<UCSZ1);
	UCSRB=(1<<TXEN);
	PORTB = 0xFF;
	while(1) {
		n++;
		sprintf(tem,"counter = %d",n);
		uart_print(tem);
		PORTB = 0xFF;
		_delay_ms(1000);
		PORTB = 0x00;
		_delay_ms(1000);
		
	}
	return 0;
}
