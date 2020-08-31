/*
 * blinkLED.c
 *
 * Created: 11.08.2020 16:41:40
 * Author : hostvind
 */ 

#define F_CPU 12000000UL
//11718 for 1 second
//divided by 25 fps = 468
#define T_TIM 155

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "main.h"
#include "avr/iom16.h"

char count_GL=252;
char count_ARR[3]={0,0,0};
char call_MODE=0xFF;

ISR (TIMER1_COMPA_vect)    // Timer1 ISR
{
	//call_MODE = (PINB & 0b00001110);
	call_MODE=0;
	if (D_SW_1_PINS & (1<<D_SW_1_PIN))
		call_MODE |= 0x02;
	if (D_SW_2_PINS & (1<<D_SW_2_PIN))
		call_MODE |= 0x04;
	if (D_SW_3_PINS & (1<<D_SW_3_PIN))
		call_MODE |= 0x08;
	dig_run(call_MODE);
	TCNT1 = 0;   // reset timer
}

int init_TIM (void)
{
	TCNT1 = 0;   // for 1 sec at 12 MHz	
	TCCR1A = 0x00;
	TCCR1B = (1<<CS10) | (1<<CS12);  // Timer mode with 1024 prescaler
	OCR1A = T_TIM;
	TIMSK = (1 << OCIE1A) ;   // Enable timer1 overflow interrupt(TOIE1)
	return 0;
}

int init_GPIO (void)
{
	DDRA = 0x00;
	DDRB = 0x00;
	DDRC = 0x00;
	DDRD = 0x00;
	
	//Blinking port
	DDRB |= (1<<PB0);
	
	//BUTTONS
	//DDRB |= (1<<PB1)||(1<<PB2)||(1<<PB3);
	D_SW_1_PORT |= (1<<D_SW_1_PIN);
	D_SW_2_PORT |= (1<<D_SW_2_PIN);
	D_SW_3_PORT |= (1<<D_SW_3_PIN);
	
	//Digit show port
	DDRC = 0xFF;
	
	DDRA = 0b11110000;
	return 0;
}


int main(void)
{
    /* Replace with your application code */
	init_GPIO();
	init_TIM();
	sei();
	char count_tmp;
    while (1) 
    {
		count_tmp=count_GL;
		for (int i=0;i<3;i++)
		{
			count_ARR[i]=count_tmp%10;
			count_tmp/=10;
		}
		dig_set (count_ARR);
		PORTB ^= (1<<PORTB0);
		count_GL++;
		_delay_ms(1000);
		
    }
}

