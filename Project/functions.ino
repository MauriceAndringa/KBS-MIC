/* 
* functions.cpp
*
* Created: 20-11-2017 14:23:43
* Author: Erwin
*/


#include "Functions.h"

// default constructor
Functions::Functions()
{
} //functions

// default destructor
Functions::~Functions()
{
} //~functions





void Functions::startTimerScreenBrightness()
{
	TCCR1A |= (1<<COM0A1);
	TCCR1A |= (1<<WGM01)|(1<<WGM00);
	TCCR1B |= (1<<CS01);
}

int Functions::readBrightnessPot()
{
	ADMUX = 0x40;								//Instellen input poort en referentiespanning
	
	ADCSRA = (1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);	//ADCklok=CPUklok/128
	ADCSRA |= (1<<ADEN);						//ADC inschakelen
	ADCSRA |= (1<<ADSC);        				//een enkele AD-conversie
	
	while (ADCSRA & (1<<ADSC)); 				//wacht op resultaat
	
	return ADC;
	
}

void Functions::screenBrightness()
{
	OCR1A = readBrightnessPot();
}

int Functions::readRandom()
{
	int rand1, rand2;
	ADMUX = 0x41;								//Instellen input poort en referentiespanning
	
	ADCSRA = (1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);	//ADCklok=CPUklok/128
	ADCSRA |= (1<<ADEN);						//ADC inschakelen
	ADCSRA |= (1<<ADSC);        				//een enkele AD-conversie
	
	
	while (ADCSRA & (1<<ADSC)); 				//wacht op resultaat
	
	rand1 = ADC;
	
		ADMUX = 0x42;								//Instellen input poort en referentiespanning
		
		ADCSRA = (1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);	//ADCklok=CPUklok/128
		ADCSRA |= (1<<ADEN);						//ADC inschakelen
		ADCSRA |= (1<<ADSC);        				//een enkele AD-conversie
		
		while (ADCSRA & (1<<ADSC)); 				//wacht op resultaat
		
	rand2 = ADC;
	
	return (rand2^2)%rand1;
	
}
