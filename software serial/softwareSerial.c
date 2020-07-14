/* 
here in this code portd5 is taken as transmitter and portd6 is taken as output
you can modify the functions with your pin value and run also change the F_CPU you can also optionally change baurd rate
serialread returns 0xFF if something happens wrong
*/

#include <avr/io.h>
#define baurdrate 9600
#define F_CPU 16000000UL
#include <util/delay.h>

void softserialwrite(char c){
	float delay = (1000000UL)/baurdrate;  //set delay
	DDRD|=1<<PORTD5;
	// start serial communication
	PORTD&=~(1<<PORTD5);
	_delay_us(delay);
	// send every bit
	for(uint8_t i=0;i<8;i++){
		if(c&&(1<<i))
			PORTD|=1<<PORTD5;
		else 
			PORTD&=~(1<<PORTD5);
		_delay_us(delay);
	}
	//stop serial communication
	PORTD|=1<<PORTD5;
	_delay_us(delay);
}
uint8_t issoftserialavaible(){
	if(PIND&(1<<PORTD6))
		return 0;
	return 1;
}
//function for reading data in character
char softserialread(){
	char data=0x00;
	float delay = (1000000UL)/baurdrate;
	// if no start bit then stop communication
	if(PIND&(1<<PORTD6))
		return 0xFF;
	_delay_us(delay);
	//read data
	for(uint8_t i=0;i<8;i++){
		if(PIND&(1<<PORTD6))
			data|=(1<<i);
		_delay_us(delay);
	}
	// if stop bit return data
	if(PIND&(1<<PORTD6))
		return data;
	// if something happens wrong return 0xFF
	return 0xFF;
	
}

int main(void)
{
	
	while (1)
	{
	}
}