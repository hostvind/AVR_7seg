#include <avr/io.h>
#include "Numbers.h"

char init_7seg	(void)
{
		DIGIT_DISP_DD = 0xFF;		
		DIGIT_SEL_DD = 0b11110000;
		return 0;
}

char dig_set(char* array)
{
	for (int i=0; i<DIGITS; i++)
		disp_arr[i]=array[i];
	return 10;
}

char dig_run(char MODE)
{	//just in case
	if (disp_select>DIGITS)
	{
		disp_select=1;
		return 1;
	}
	//clear before new input
	dig_sel(0);
	
	//work on actual displays only
	if (MODE&(1<<disp_select))
	{
		dig_sel(disp_select);
		dig_show(disp_arr[disp_select-1]);
	}

	disp_select++;
	if (disp_select>DIGITS)
		disp_select=1;
	return 0;
}

char dig_sel (char selection)
{
	char result=0;
	switch (selection)
	{
		case 0:
			DIGIT_SEL_PORT &= ~(1<<DIGIT1_PIN);
			DIGIT_SEL_PORT &= ~(1<<DIGIT2_PIN);
			DIGIT_SEL_PORT &= ~(1<<DIGIT3_PIN);
			break;
		case 1:
			DIGIT_SEL_PORT |= (1<<DIGIT1_PIN);
			DIGIT_SEL_PORT &= ~(1<<DIGIT2_PIN);
			DIGIT_SEL_PORT &= ~(1<<DIGIT3_PIN);
			break;
		case 2:
			DIGIT_SEL_PORT &= ~(1<<DIGIT1_PIN);
			DIGIT_SEL_PORT |= (1<<DIGIT2_PIN);
			DIGIT_SEL_PORT &= ~(1<<DIGIT3_PIN);
			break;
		case 3:
			DIGIT_SEL_PORT &= ~(1<<DIGIT1_PIN);
			DIGIT_SEL_PORT &= ~(1<<DIGIT2_PIN);
			DIGIT_SEL_PORT |= (1<<DIGIT3_PIN);
			break;
		default:
			result=2;
			break;
	}
	return result;
}

char dig_show (char digit)
{
	if (digit>9)
		return 1;
	//DIGIT_DISP_PORT = 0xFF;
	DIGIT_DISP_PORT = (nums[digit]);
	return 0;
}