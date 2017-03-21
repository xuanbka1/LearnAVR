#define F_CPU 8000000
#include <avr/io.h>
#include  <avr/interrupt.h>
#include <util/delay.h>
#include <avr/sfr_defs.h>


#define  CHOP PD5
#define EN PD6
#define DIR PB1
#define Left PD2
#define Right PD2


static uint32_t count =0;
int main()
{
	DDRB = 0xFF;
	TCCR0 |=  (1<<CS01);
	TCNT0 =186;
	TIMSK = 1<<TOIE0;

	sei();
	
	DDRC |= (1<<PC0);  //Nakes first pin of PORTC as Output
	DDRD |= 1<<PD6;
	// OR DDRC = 0x01;
	DDRD &= ~(1<<PD2);//Makes firs pin of PORTD as Input
	DDRD &= ~(1<<PD3);//Makes firs pin of PORTD as Input
	// OR DDRD = 0x00; //Makes all pins of PORTD input
	PORTB &=~ (1<<0);

	while(1) //infinite loop
	{
	}

}

// generate PWM 50%
ISR (TIMER0_OVF_vect){
	
	TCNT0 =186;
	count ++;
	if(count >716800)
	PORTB &=~ (1<<0);
	else
	PORTB ^= (1<<0);
}
