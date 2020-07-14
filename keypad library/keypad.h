// keypad function which returns key pressed when called.
// port must be given as input with &before it eg: &PORTD
// returns rows and columns in keypad data form defined before.
// in case of fail reading or key is not pressed returns rows and columns as 4

#ifndef F_CPU
#warinig "util/delay.h not included or included after this library"
#endif
//time delay between setting pins low and reading form input.
#define keypad_excdelay 1
//a macro function to set custom delay time.
#define keypad_set_delay(n)  (#define keypad_excdelay n)


//defining new data type for simple usage and saving space.
typedef struct {
	uint8_t row : 2;
	uint8_t column :2;
} keypad;


keypad keypad_getkey(volatile uint8_t *port)
{
	uint8_t data=0;
	keypad key;
	key.row=4;                         
	key.column=4;                      //initialize column and row to 4 value which indicates error.
	*(port-1) =0xF0;                   //set columns as output and rows as input. port-1 indicates ddr for corresponding port
	*(port) =0x0F;                     //set columns low and rows with pull_up resistors
	_delay_ms(keypad_excdelay);        //wait for settings to take effect
	data=*(port-2)^0x0F;               //reads row number. port -2 indicates pin for corresponding port
	if(data==0)
	return key;
	if(data==8)
	key.row= 3;
	else key.row= data>>1;
	*(port-1) =0x0F;
	*(port) =0xF0;
	_delay_ms(keypad_excdelay);
	data|=*(port-2)^0xF0;               //reads column number.
	data=data>>4;
	if(data==8)
	key.column= 3;
	else key.column= data>>1;
	return key;
}