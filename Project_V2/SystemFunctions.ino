/*
* SystemFunctions.cpp
*
* Created: 29-11-2017 11:09:18
* Author: Erwin
*/


#include "SystemFunctions.h"
#include "Map.h"

#define NUNCHUCKADRESS 0x52

enum nuchuckResult{ UP = 1, RIGHT, DOWN, LEFT, SELECT };

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

uint8_t SystemFunctions::readNunchuck()
{
	uint8_t result = 0;
	uint8_t buffer[6];
	uint8_t i=0;
	
	Wire.requestFrom (0x52, 6);     // request data from nunchuck
	while (Wire.available ()) {
		// receive byte as an integer
		buffer[i] = decodeNunchuck(Wire.read());
		i++;
	}
	
	sendRequest();
	
	if (buffer[1]>200)
	result = 1;
	else if (buffer[1]<50)
	result = 3;
	else if (buffer[0]> 200)
	result = 2;
	else if (buffer[0] < 50)
	result = 4;
	else if (!((buffer[5] >> 0) & 1))
	result = 5;		// Z-button

	return result;	
}

uint8_t SystemFunctions::calcX(uint8_t loc)
{
	return loc%13*GRID;
}

uint8_t SystemFunctions::calcY(uint8_t loc)
{
	return loc/13*GRID;
}

char SystemFunctions::decodeNunchuck(char x)
{
	x = (x ^ 0x17) + 0x17;
	return x;
}

void SystemFunctions::sendRequest()
{
	Wire.beginTransmission(NUNCHUCKADRESS);   // transmit to Nunchcuk adress
	Wire.write(0x00);
	Wire.endTransmission();
}