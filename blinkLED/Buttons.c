#include <avr/io.h>
#include "Buttons.h"
#include "main.h"

char init_buttons(void)
{
	BUTTONS_DD	&=	~(1<<BUTTON1_PIN);
	BUTTONS_PORT |= (1<<BUTTON1_PIN);
	butt_state = 0;
	b1_count = 0;
	return 0;
}

char butt_job(void)
{
	if (!(BUTTONS_PINS & (1<<BUTTON1_PIN)))
		//PORTB &= ~(1<<PB0);
		{
			butt_state |= (1<<0);
			b1_count++;
		}
	else
		{
			if (butt_state & (1<<0))
			{
				if (b1_count<BUTTON_SHORT_DELAY)
					;
				else if (b1_count>BUTTON_LONG_DELAY)
					//timer_mode(BACK);
					timer_mode(STOP);
				else
					timer_mode(PAUSE);
				b1_count=0;
				butt_state &= ~(1<<0);	
			}
		}
	
	return 0;
}