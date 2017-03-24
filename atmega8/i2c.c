
#define F_CPU 8000000  // external crystal
#include <avr/io.h>
#include <util/delay.h>


#define ERROR 1
#define SUCCESS (!ERROR)

#define address 0x90
#define  Read 1
#define  Write 0

void TWIInit(void);
void TWIStart(void);
void TWIStop(void);
void TWIWrite (uint8_t u8data);
uint8_t TWIReadACK(void);
uint8_t TWIReadNACK(void);
//void uint8_t Write (uint16_t addr, uint8_t data);

uint8_t static dac_value =0;
int main(void)
{
	
	TWIStart();
	TWIWrite(0x90);
	 TWIWrite(0x40);
	 TWIWrite(0x80);

	//TWIStop();
    /* Replace with your application code */
    while (1) 
    {
		_delay_ms(100);
		dac_value +=5;
		 TWIWrite(dac_value);
			
		
		
    }
}

void TWIInit(){
	//set SCL to 100kHz
	 TWSR = 0x00;  //TWSR =0
	 TWBR = 0x20; //TWBR =32
	 //enable TWI
	 TWCR |= (1<<TWEN);
}

void TWIStart()
{
	  TWCR |= (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
	  while ((TWCR & (1<<TWINT)) == 0);
}

//send stop signal
void TWIStop(void)
{
	TWCR |= (1<<TWINT)|(1<<TWSTO)|(1<<TWEN);
}

void TWIWrite (uint8_t u8data)
{
	TWDR = u8data;
	TWCR |= (1<<TWINT)|(1<<TWEN);
	while ((TWCR & (1<<TWINT)) == 0);
}

uint8_t TWIReadACK(void)
{
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWEA);
	while ((TWCR & (1<<TWINT)) == 0);
	return TWDR;
}
//read byte with NACK
uint8_t TWIReadNACK(void)
{
	TWCR = (1<<TWINT)|(1<<TWEN);
	while ((TWCR & (1<<TWINT)) == 0);
	return TWDR;
}

uint8_t TWIGetStatus(void)
{
	uint8_t status;
	//mask status
	status = TWSR & 0xF8;
	return status;
}
