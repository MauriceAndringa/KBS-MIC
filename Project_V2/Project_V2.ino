
// INCLUDES
// Libraries
#include <MI0283QT9.h>
//#include <BMPheader.h> //todo is deze include nodig?
#include <Wire.h>

// Header Files
#include "SystemFunctions.h"
#include "MainMenu.h"
#include "Map.h"

// DEFINES
#define TEST 
#define EASY 
#define MEDIUM 
#define HARD 

// Global Variables
View currentView	= NONE;
View requestedView	= MENU;

// Objects
MI0283QT9 LCD;
MainMenu mainMenu(&LCD, &currentView, &requestedView);
Map level(&LCD);

//Function declaration
void initializePins();
void initializeRegisters();
void initializeNunchuck();

//Code
int main (void)
{
	//Startup sequence
	
	init();
	
	//Initialize pins
	initializePins();
	
	//Initialize registers
	initializeRegisters();
	
	//Initialize nunchuck communication
	initializeNunchuck();
	
	// LCD setup
	LCD.begin();
	LCD.fillScreen(RGB(255,255,255));
	LCD.touchStartCal();
	
	//Debug stuff
	Serial.begin(9600);
	
	for (;;)
	{
		// change led brightness if it is changed
		SystemFunctions::screenBrightness();
		Serial.println (SystemFunctions::readNunchuck());
		
		if(currentView != requestedView){
			
			currentView = requestedView;
			
			switch(currentView){
				
				case MENU:
					mainMenu.draw();
					break;
				
				case GAME:
					level.drawMap();
					break;
						
			}
		}

		mainMenu.listenToTouchInput();
		//Serial.println(((rand() / RAND_MAX) % 3) + 1);
		
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

void initializeNunchuck()
{
	Wire.begin();
	Wire.beginTransmission(0x52);     // transmit to device 0x52
	Wire.write(0x40);            // sends memory address
	Wire.write(0x00);            // sends sent a zero.
	Wire.endTransmission();     // stop transmitting
}

