
#define F_CPU 8000000
#include <avr/io.h>
#include <avr/sfr_defs.h>
#include <util/delay.h>

void i2c_start (void)
{
/* step 1+2+3. initilize START and check codition START successfull.*/
// step1//
	TWCR |= (1<<TWSTA) | (1<<TWEN) | (1<<TWINT); //start =1; enable i2c; write 1 to TWINT

/*
2.TWINT set.
Status code indicates
START condition sent
*/
 while (!(TWCR & (1<<TWINT))); // if TWINT = 1, start ok, break while
 
 /*After a START condition has been transmitted, 
 the TWINT Flag is set by hardware,
  and the status code in TWSR will be 0x08
*/ 
 // step3//
 if((TWSR&0xF8) !=0x08) return TWSR; 

}


// write address slaver +r/w//
void i2c_write_SLA (uint8_t add_sla){
	uint8_t read = 1;
	uint8_t write = 0;
// step 4//	
	TWDR = (add_sla<<1) | read;
	TWCR = (1<<TWINT) | (1<<TWEN); // clear bit TWINT, enable i2c
	while (!(TWCR & (1<<TWINT))); // if TWINT = 1, start ok, break while
	if((TWSR&0xF8) !=0x18) return TWSR; //device address send error, escape anyway . 0x18 is code in TWSR	
}

//step5 + 6 //
void i2c_write_adress(uint8_t address)
{
	TWDR = address;
	TWCR = (1<<TWINT) | (1<<TWEN); // clear bit TWINT, enble i2c
	if((TWSR&0xF8) !=0x28) return TWSR;  // 0x28 , code Data byte has been transmitted; ACK has been received
}

void i2c_write_data(uint8_t data)
{
	TWDR = data;
	TWCR = (1<<TWINT) | (1<<TWEN); // clear bit TWINT, enble i2c
	if((TWSR&0xF8) !=0x28) return TWSR;  // 0x28 , code Data byte has been transmitted; ACK has been received
}

void i2c_write_array_data(uint8_t data[] , uint8_t len)
{
	for (uint8_t i=0; i < len; i++)
	{
		i2c_write_data(data[i]);
	}
}

void i2c_stop (void)
{
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
}



int main(void)
{
    /* Replace with your application code */
    while (1) 
    {
    }
}
