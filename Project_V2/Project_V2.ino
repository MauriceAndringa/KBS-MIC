
// INCLUDES
// Libraries
#include <MI0283QT9.h>

// Header Files
#include "SystemFunctions.h"
#include "MainMenu.h"
#include "Map.h"

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

//Code
int main (void)
{
	float difficulty = 0.7;
	
	//Startup sequence
	init();
	
	//Initialize pins
	initializePins();
	
	//Initialize registers
	initializeRegisters();
	
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
		
		// check if the the requested view has changed
		if(currentView != requestedView){
			
			currentView = requestedView;
			
			// decide which view to draw
			switch(currentView){
				
				// draw the main menu
				case MENU:
					mainMenu.draw();
					break;
				
				// draw the screen
				case GAME:
					level.drawMap(difficulty);
					break;
						
			}
		}

		mainMenu.listenToTouchInput();
		
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

