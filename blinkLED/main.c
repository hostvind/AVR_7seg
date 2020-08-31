/*
 * blinkLED.c
 *
 * Created: 11.08.2020 16:41:40
 * Author : hostvind
 */ 

#define F_CPU 12000000UL
//11718 for 1 second
//divided by 25 fps = 468
#define T_TIM 467

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "main.h"
#include "avr/iom16.h"
#include "Numbers.h"

char count_GL=250;
char disp_arr[3]={0,5,2};
char disp_select=1;

ISR (TIMER1_COMPA_vect)    // Timer1 ISR
{
	if (!disp_select)
	{
		disp_select=0;
	}
	else if (disp_select>3)
	{
		disp_select=1;
	}
	else
	{
		disp_select++;
	}
	dig_sel (disp_select);
	TCNT1 = 0;   // reset timer
}

int init_TIM (void)
{
	TCNT1 = 0;   // for 1 sec at 12 MHz	
	TCCR1A = 0x00;
	TCCR1B = (1<<CS10) | (1<<CS12);;  // Timer mode with 1024 prescaler
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
	DDRB |= (1<< PB0);
	
	//Digit show port
	DDRC = 0xFF;
	
	//Digit selector port
	/*
	DDRA &= ~(1<<PA4);
	DDRA &= ~(1<<PA5);
	DDRA &= ~(1<<PA6);
	DDRA &= ~(1<<PA7);
	*/
	DDRA = 0b11110000;
	return 0;
}

char dig_sel (char selection)
{
	disp_select = selection;
	if (selection > 3)
		return 1;
	else if (!selection)	//turn off
	{
		DIGIT_SEL_PORT |= (1<<DIGIT1_PIN);
		DIGIT_SEL_PORT |= (1<<DIGIT2_PIN);
		DIGIT_SEL_PORT |= (1<<DIGIT3_PIN);
		return 0;
	}
	switch (selection)
	{
	case 0: //just in case
		DIGIT_SEL_PORT |= (1<<DIGIT1_PIN);
		DIGIT_SEL_PORT |= (1<<DIGIT2_PIN);
		DIGIT_SEL_PORT |= (1<<DIGIT3_PIN);
		break;
	case 1:
		DIGIT_SEL_PORT &= ~(1<<DIGIT1_PIN);
		DIGIT_SEL_PORT |= (1<<DIGIT2_PIN);
		DIGIT_SEL_PORT |= (1<<DIGIT3_PIN);
		break;
	case 2:
		DIGIT_SEL_PORT |= (1<<DIGIT1_PIN);
		DIGIT_SEL_PORT &= ~(1<<DIGIT2_PIN);
		DIGIT_SEL_PORT |= (1<<DIGIT3_PIN);
		break;
	case 3:
		DIGIT_SEL_PORT |= (1<<DIGIT1_PIN);
		DIGIT_SEL_PORT |= (1<<DIGIT2_PIN);
		DIGIT_SEL_PORT &= ~(1<<DIGIT3_PIN);
		break;
	default:
		return 2;
		break;
	}
	dig_show(disp_arr[selection-1]);
	return 0;
}

char dig_show (char digit)
{
	if (digit>9)
		return 1;
	DIGIT_DISP_PORT = nums[digit];
	return 0;
}

int main(void)
{
    /* Replace with your application code */
	init_GPIO();
	init_TIM();
	sei();
	dig_sel(5);
	char display;
    while (1) 
    {
		display=count_GL;
		for (int i=0;i<3;i++)
		{
			disp_arr[i]=display%10;
			display/=10;
		}
		
		PORTB ^= (1<<PORTB0);
		count_GL++;
		_delay_ms(1000);
		
    }
}

