/* 
* functions.cpp
*
* Created: 20-11-2017 14:23:43
* Author: Erwin
*/


#include "functions.h"

// default constructor
functions::functions()
{
} //functions

// default destructor
functions::~functions()
{
} //~functions





void functions::startTimerScreenBrightness()
{
	TCCR1A |= (1<<COM0A1);
	TCCR1A |= (1<<WGM01)|(1<<WGM00);
	TCCR1B |= (1<<CS01);
}

int functions::readBrightnessPot()
{
	ADMUX = 0x40;								//Instellen input poort en referentiespanning
	
	ADCSRA = (1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);	//ADCklok=CPUklok/128
	ADCSRA |= (1<<ADEN);						//ADC inschakelen
	ADCSRA |= (1<<ADSC);        				//een enkele AD-conversie
	
	while (ADCSRA & (1<<ADSC)); 				//wacht op resultaat
	
	return ADC;
	
}

void functions::screenBrightness()
{
	OCR1A = readBrightnessPot();
}
