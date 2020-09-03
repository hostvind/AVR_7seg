/*
 * blinkLED.c
 *
 * Created: 11.08.2020 16:41:40
 * Author : hostvind
 */ 

#define F_CPU 12000000UL
//11718 for 1 second
//divided by 25 fps = 468
//divided by 3 displays = 156
#define T_TIM 100

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "main.h"
#include "avr/iom16.h"

unsigned int count_GL=65530;
char count_ARR[3]={0,0,0};
char call_MODE=0xFF;
unsigned int count_tmp;

ISR (TIMER1_COMPA_vect)    // Timer1 ISR
{
	TCNT1 = 0;   // reset timer
	call_MODE=0xFF;
	//if (D_SW_1_PINS & (1<<D_SW_1_PIN))
		//call_MODE |= 0x02;
	//if (D_SW_2_PINS & (1<<D_SW_2_PIN))
		//call_MODE |= 0x04;
	//if (D_SW_3_PINS & (1<<D_SW_3_PIN))
		//call_MODE |= 0x08;
	dig_run(call_MODE);
	butt_job();

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
	
	PORTD = 0x00;
	
	//Blinking port
	DDRB |= (1<<PB0);
	
	//BUTTONS
	init_buttons();
	
	//Digit show port
	init_7seg();
	return 0;
}

char timer_mode(TIM_STATE MODE)
{
	if (MODE==timer_state)
		timer_state=RUN;
	else
		timer_state=MODE;
	return 0;
}

int main(void)
{
    /* Replace with your application code */
	init_GPIO();
	init_TIM();
	timer_state = RUN;
	sei();
    while (1) 
    {
		
		switch (timer_state)
		{
			case STOP:
				count_GL=0;
				break;
			case RUN:
				count_GL++;
				break;
			case BACK:
				count_GL--;
				break;
			case PAUSE:
				count_GL=count_GL;
				break;
			default:
				break;
		}
		
		
		count_tmp=count_GL;
		for (int i=0;i<3;i++)
		{
			count_ARR[i]=count_tmp%10;
			count_tmp/=10;
		}
		dig_set (count_ARR);
		PORTB ^= (1<<PORTB0);
		_delay_ms(500);
		PORTB ^= (1<<PORTB0);
		_delay_ms(500);
		
    }
}

