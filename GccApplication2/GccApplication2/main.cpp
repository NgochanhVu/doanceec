#define F_CPU 1000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

int button;
int time_s = 65536 - (1  * (1000000 / 1024)); // 5s ngat trang


int main(void)
{
	DDRB |= 0xff;			/* define LED port direction is output */
	PORTB = 0xff;
	
	GICR |= (1<<INT0);
	MCUCR |= (1<<ISC01);
	TCCR1B |= (1<<CS10 | 1<<CS12); // CS12=1, CS11=0, CS10=1: chon Prescaler =1024
	TCNT1 = time_s;
	TIMSK=(1<<TOIE1);//cho phep ngat khi co tran o T/C1
	
	sei();                       //set bit I cho phep ngat toan cuc
	char array[]={0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90};
	///* write hex value for CA display from 0 to 9 */
	
	button = 0;
	while(1)
	{
		PORTB = array[button]; /* write data on to the LED port */
	}

	return 0;
}

ISR (TIMER1_OVF_vect ){
	//count++;
	button++;
	TCNT1 = time_s;
	if (button > 9) button = 0;
}



ISR(INT0_vect){
	button++;
	if (button > 9) button = 0;
}