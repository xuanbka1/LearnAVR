/*
#define F_CPU 8000000

#include <avr/io.h>
#include  <avr/interrupt.h>
#include <util/delay.h>
#include <avr/eeprom.h>
#include <avr/sfr_defs.h>


#define CHOP_ON  (PORTD |= (1<<PD5));
#define CHOP_OFF (PORTD |= (1<<PD5));

#define EN_ON    (PORTD |= (1<<PD6));
#define EN_OFF    (PORTD &=~ (1<<PD6));

#define DIR_ON   (PORTB |= (1<< PB1));
#define DIR_OFF   (PORTB &=~ (1<< PB1));

#define Left PD2
#define Right PD3

#define STOP_ON  PORTC &=~(1<<PC0);
#define STOP_OFF PORTC |=(1<<PC0);

 static uint8_t enable = 0;
 static uint16_t cnt = 0;
 
 
int main()
{
	
	DDRB |= (1<< PB0); // pin output PWM
	TCCR0 |= (1<<CS01)  ; // prescale Timer 0
	TCNT0 = 131;
	TIMSK = 1<<TOIE0; // interrupt timer0

	sei();
	
	DDRD |=  ( 1<<PD6 | 1<<PD5 );     //output for DIR
	DDRB |= 1<<PB1;     //output for ENABLE pin
	
    DDRD &= ~(1<< Left);  //PD1 is Input, button LEFT
	DDRD &= ~(1<< Right);  //PD2 is Input, Button RIGHT
	
	EN_OFF; // enable always OFF
	
	PORTB &=~ (1<<PB0); // initial Fulse OFF
	
	CHOP_OFF;
	
	
while(1) //infinite loop
	{
		 //If switch is pressed
		if (bit_is_clear(PIND, Left))   //If switch is pressed-> PD1 =0
			{
				STOP_OFF;
				DIR_ON; // DIR = LEFT
				enable = 1;
			}
		else if (bit_is_clear(PIND, Right)) //If switch is pressed
			{
				 STOP_OFF;
				 DIR_OFF;  // DIR = RIGHT
				 enable = 1;
			}
		else
			{
			PORTB &=~ (1<<PB0); // pulse =0 , motor stop
			STOP_ON;
			enable = 0;			
			}
			
	} // end while
	
	
	return 0;
}


// generate PWM 50%
ISR (TIMER0_OVF_vect){
	
	if(enable==0)
	{	
		PORTB &=~ (1<<PB0);
	
	}
	else
	{
		cnt++;
		TCNT0 = 131;
		if(cnt==1000)
		enable=0;
		PORTB ^= (1<<PB0);
	}
}
*/

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

