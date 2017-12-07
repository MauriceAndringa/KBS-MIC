
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
#include "Bomb.h"

// define if the microcontroller is a slave or master
#define IS_SLAVE 0

// Global Variables
View currentView	= NONE;
View requestedView	= MENU;
uint8_t resultNunchuck;


// Objects
MI0283QT9 LCD;
MainMenu mainMenu(&LCD, &currentView, &requestedView);
Bomb bomb(&LCD);
Map level(&LCD, &bomb);

#if (IS_SLAVE == 0)
	Player internalPlayer({14, 0, 14}, &LCD, &level);
	Player externalPlayer({128, 0, 128}, &LCD, &level);
#else
	Player internalPlayer({128, 0, 128}, &LCD, &level);
	Player externalPlayer({14, 0, 14}, &LCD, &level);
#endif

//Function declaration
void initializePins();
void initializeRegisters();
void initializeNunchuck();

//Code
int main (void)
{
	float difficulty = 0.7;
	unsigned long internalPlayerDropBombTimer; // keeps the time when the bomb is dropped for internalPlayer
	uint8_t bombDropped; // this variable checks if a bomb dropped and hasn't exploded yet.
	
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
	
	// initialize variables
	uint8_t internalBomblocationX;
	uint8_t internalBomblocationY;
	
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
					internalPlayer.drawPlayer();
					externalPlayer.drawPlayer();
					break;
						
			}
		}
		
		if(currentView == GAME){
			resultNunchuck = SystemFunctions::readNunchuck();
			if (resultNunchuck!= 0&&resultNunchuck!=5)
			{
				internalPlayer.move(resultNunchuck);

			} else 
				
				// check if button Z is pushed(button Z returns value 5)
				if(resultNunchuck == 5){
					internalPlayerDropBombTimer = millis();
					internalBomblocationX = internalPlayer.getLocationX();
					internalBomblocationY = internalPlayer.getLocationY();
					
					level.updateLevel(internalBomblocationX, internalBomblocationY, 4);
					bombDropped = 1;
					//bomb.drawBomb(internalBomblocationX, internalBomblocationY);
				}
				
			if(millis() >= internalPlayerDropBombTimer + 3000 && bombDropped){
				Serial.println("Bomb exploding");
				level.updateLevel(internalBomblocationX, internalBomblocationY, 2);
				bombDropped = 0;
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

void initializeNunchuck()
{
	Wire.begin();
	Wire.beginTransmission(0x52);     // transmit to device 0x52
	Wire.write(0x40);            // sends memory address
	Wire.write(0x00);            // sends sent a zero.
	Wire.endTransmission();     // stop transmitting
}

