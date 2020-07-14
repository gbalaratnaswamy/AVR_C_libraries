/*

*/

#include <avr/io.h>
#define delaybwdigits 5 // delay between digits displayed
uint8_t seg[10]={0xFC,0x60,0xDA,0xF2,0x66,0xB6,0xBE,0xE0,0xFE,0xF6};
void sevseg(int n, int p){
	for(uint8_t i=0;i<4;i++){
		PORTB=~(1<<i);
		PORTD=seg[n%10]|(i==p);
		n=n/10;
		_delay_ms(delaybwdigits);
	}
}


int main(void)
{
	
	while (1)
	{
	}
}