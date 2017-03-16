
#define F_CPU 8000000
#include <avr/io.h>
#include  <avr/interrupt.h>
#include <util/delay.h>
#include <avr/eeprom.h>


#define  CHOP PD5
#define EN PD6
#define DIR PB1
#define Left PD1
#define Right PD2

 static uint8_t val;
 
int main()
{
	DDRB |= (1<< PB0); // pin output PWM
	TCCR0 |= (1<<CS01)  ; // prescaler Timer 0
	TCNT0 =0;
	TIMSK = 1<<TOIE0; // interrupt timer0

	sei();
	
	DDRD |= 1<<PD6;  //output for DIR
	DDRB |= 1<<PB1;    //output for ENABLE pin
	
    DDRD &= ~(1<<PD1); //PD1 is Input
	DDRD &= ~(1<<PD2); //PD2 is Input
	
while(1) //infinite loop
{
	
	if(PIND & (1<<PIND1)) //If switch is pressed
	{
		PORTB &=~ (1<<PB1);    //Turns EN ON
		PORTD |= (1<<PD6); // DIR =0
		val =100;
	}
	else if (PIND & (1<<PIND2)) //If switch is pressed
	{
	 
	 PORTB |= (1<<PB1);  // DIR =1
	 PORTD |= (1<<PD6);  // EN ON 
	 val =100;
	}
	else
	{
			PORTB &=~ 1<<PB1;    //Turns OFF Enable
			PORTD &=~ 1<<PD6;    // 
			val =0;			
	}


}


	return 0;
}


// generate PWM 50%
ISR (TIMER0_OVF_vect){
	
	TCNT0 = val;
	PORTB ^= (1<<0);
}


