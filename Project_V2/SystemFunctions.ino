/* 
* SystemFunctions.cpp
*
* Created: 29-11-2017 11:09:18
* Author: Erwin
*/


#include "SystemFunctions.h"

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