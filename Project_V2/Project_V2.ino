
// INCLUDES
// Libraries
#include <MI0283QT9.h>
//#include <BMPheader.h> //todo is deze include nodig?
#include <Wire.h>

// Header Files
#include "SystemFunctions.h"
#include "MainMenu.h"
#include "Map.h"
#include "Player.h"

// define if the microcontroller is a slave or master
#define IS_SLAVE 0

// Global Variables
View currentView	= NONE;
View requestedView	= MENU;

// Objects
MI0283QT9 LCD;
MainMenu mainMenu(&LCD, &currentView, &requestedView);
Map level(&LCD);

#if (IS_SLAVE == 0)
	Player internalPlayer({25, 25, 0, 0}, &LCD, &level);
	Player externalPlayer({225, 185, 0,0}, &LCD, &level);
#else
	Player internalPlayer({225, 185, 0, 0}, &LCD, &level);
	Player externalPlayer({25, 25, 0, 0}, &LCD, &level);
#endif

//Function declaration
void initializePins();
void initializeRegisters();
void initializeNunchuck();

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
		
		if(currentView == GAME){
			internalPlayer.drawPlayer();
			externalPlayer.drawPlayer();
			delay(250);
			internalPlayer.moveRight();
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

void initializeNunchuck()
{
	Wire.begin();
	Wire.beginTransmission(0x52);     // transmit to device 0x52
	Wire.write(0x40);            // sends memory address
	Wire.write(0x00);            // sends sent a zero.
	Wire.endTransmission();     // stop transmitting
}

