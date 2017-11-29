
// INCLUDES
// Libraries
#include <MI0283QT9.h>
//#include <SD.h>
#include <BMPheader.h> //todo is deze include nodig?

// Header Files
#include "SystemFunctions.h"

// DEFINES
#define TEST 
#define EASY 
#define MEDIUM 
#define HARD 

// Global Variables
MI0283QT9 LCD;
//SystemFunctions SF;



//Function declaration
void initializePins();
void initializeRegisters();

//Code
int main (void)
{
	//Startup sequence
	
	init();
	
	//Initialize pins
	initializePins();
	
	//Initialize registers
	initializeRegisters();
	
	// LCD setup
	LCD.begin();
	LCD.fillScreen(RGB(255,255,255));
		
	// initialize SD-card
//	initSD();
	
	//Debugstuff
	Serial.begin(9600);
	
	for (;;)
	{
		SystemFunctions::screenBrightness();
		
		
	}
	
	
}

// Functions
void initializePins()
{
	DDRB |=  (1 <<DDB1);		//Outputpoort van achtergrondlicht
	DDRC &= ~(1 << DDC0);		//Inputpoort van potmeter (analogPin0), en 2 analoge poorten voor het genereren van willerkeurige input.
	PORTC |= (1 <<PORTC0);		//instellen pull-up weerstand
}

void initializeRegisters()
{
	//ADC register
	ADCSRA = (1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);	//ADCklok=CPUklok/128
	ADCSRA |= (1<<ADEN);						//Enable ADC
	
	//PWM register
	TCCR1A |= (1<<COM0A1);						
	TCCR1A |= (1<<WGM01)|(1<<WGM00);
	TCCR1B |= (1<<CS01);
}

