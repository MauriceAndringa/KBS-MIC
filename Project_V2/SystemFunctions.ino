/* 
* SystemFunctions.cpp
*
* Created: 29-11-2017 11:09:18
* Author: Erwin
*/


#include "SystemFunctions.h"

volatile uint32_t seed;
volatile int8_t nrot;
	
ISR(WDT_vect)
{
	nrot--;
	seed = seed << 8;
	seed = seed ^ TCNT1L;
}

// default constructor
SystemFunctions::SystemFunctions()
{
} //SystemFunctions

// default destructor
SystemFunctions::~SystemFunctions()
{
} //~SystemFunctions

int SystemFunctions::readAnalog(uint8_t pin)
{
	if (pin<6)										//Check if pin exists.
	{	
		ADMUX = 0x40;								//Declare Reference
		ADMUX |= pin;								//Define pin
		

		ADCSRA |= (1<<ADSC);        				//Single AD-conversion
	
		while (ADCSRA & (1<<ADSC)); 				//Wait for result
		
		return ADC;
	} else 
		return 0;									//Error value
}

void SystemFunctions::screenBrightness()
{
	
	OCR1A = readAnalog(0);		//Save ADC value from A0 in OCR1A to change LCD brightness
	//Serial.println(OCR1A);
}

void SystemFunctions::createRandomSeed()
{
	seed = 0;
	nrot = 32; // Must be at least 4, but more increased the uniformity of the produced
	// seeds entropy.
	// The following five lines of code turn on the watch dog timer interrupt to create
	// the seed value
	cli();
	MCUSR = 0;
	_WD_CONTROL_REG |= (1<<_WD_CHANGE_BIT) | (1<<WDE);
	_WD_CONTROL_REG = (1<<WDIE);
	sei();

	while (nrot > 0); // wait here until seed is created

	// The following five lines turn off the watch dog timer interrupt
	cli();
	MCUSR = 0;
	_WD_CONTROL_REG |= (1<<_WD_CHANGE_BIT) | (0<<WDE);
	_WD_CONTROL_REG = (0<< WDIE);
	sei();
}

uint32_t SystemFunctions::getRandomSeed()
{
	SystemFunctions::createRandomSeed();
	return seed;
}