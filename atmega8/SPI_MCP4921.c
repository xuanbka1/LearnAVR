/*
 * SPI_ATMEGA8.c

 * Author : Xuanbka1
 */ 

#define  F_CPU 8000000
#include <util/delay.h>
#include <avr/io.h>
#include <stdio.h>
#include <avr/sfr_defs.h>

#define set_bit(port, bit)       (port)  |= (1<<(bit))
#define clear_bit(port, bit)     (port) &=~ (1<<(bit))

#define SPI_PORT PORTB
#define SPI_DDR DDRB

#define SCK_PIN PB5
#define MISO_PIN PB4
#define MOSI_PIN PB3
#define SS_PIN PB2

#define ADDRESS_PORT PORTB
#define ADDRESS_DDR  DDRB

static uint16_t dac_value =0;

void SPI_Init (void)
{
	SPI_DDR |= (1<<SCK_PIN) | (1<<MOSI_PIN);
	SPI_PORT|= (1<<MISO_PIN);
	SPCR |= (1<<MSTR); // chip is master
	SPCR |= (1<<SPIE) | (1<<SPE) | (1<<SPR0) | (1<<SPR1);
	SPCR &=~ (1<<DORD); // MSB tranfer
	SPCR &=~ (1<<CPOL); // mode 0
	SPCR &=~ (1<<CPHA); // mode 0
	//SPCR &=~ (SPR1); //
	SPSR |= (1<<SPI2X); // speed = F_OSC/16 = 1Mhz	
	
// setup pin address//
	ADDRESS_PORT |= (1<<SS_PIN);
	ADDRESS_DDR |= (1<<SS_PIN);
		
}

void SPI_Transmit (uint16_t data){
	
	//clear_bit(ADDRESS_PORT, SS_PIN);  // chip select = 0, select slaver
	SPDR = data;
	while (bit_is_clear(SPSR, SPIF));  // wait for SPIF =1, tranfer complete
	//set_bit(ADDRESS_PORT,SS_PIN) ;     // chip select = 1, ignore slaver
}
void writeMCP492x(uint16_t data) {
	
	
clear_bit(ADDRESS_PORT,SS_PIN);
 SPI_Transmit(data>>8 | 0x30);
 SPI_Transmit(data & 0x0FF);

set_bit(ADDRESS_PORT,SS_PIN);
}

int main(void)
{
    SPI_Init();
	_delay_ms(100);
	
	clear_bit(ADDRESS_PORT,SS_PIN);
    while (1) 
    {
		dac_value +=1;
		writeMCP492x(dac_value);
    }
	return 0;
}

