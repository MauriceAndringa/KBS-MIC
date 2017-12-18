// INCLUDES
// Libraries
#include <MI0283QT9.h>
#include <Wire.h>

// Header Files
#include "SystemFunctions.h"
#include "MainMenu.h"
#include "Map.h"
#include "Player.h"
#include "Bomb.h"
#include "Highscore.h"

// define if the microcontroller is a slave or master
#define IS_SLAVE 0

// Global Variables
View currentView	= NONE;
View requestedView	= MENU;

// Objects
MI0283QT9 LCD;
MainMenu mainMenu(&LCD, &currentView, &requestedView);
Highscore highscore(&LCD, &currentView, &requestedView);
Bomb bomb(&LCD);
Map level(&LCD, &bomb);


#if (IS_SLAVE == 1)
	Player internalPlayer({14, 0, 14}, &LCD, &level, 1);
	Player externalPlayer({128, 0, 128}, &LCD, &level, 0);
#else
	Player internalPlayer({128, 0, 128}, &LCD, &level, 1);
	Player externalPlayer({14, 0, 14}, &LCD, &level, 0);
#endif

//Function declaration
void initializePins();
void initializeRegisters();
void initializeNunchuck();

//Code
int main (void)
{
	// initialize variables
	uint8_t internalBomblocation;
	uint8_t externalBombLocation;
	//uint8_t bombDropped = 0; // this variable keeps check if a bomb dropped.
	uint8_t readyForEffect = 0; // this vaiable checks if the bomb animation is ready to be shown.
	//uint32_t doNotDrawPlayer = 0; // this variables is a timer that stops the redraw of the player for 0.5 sec unless the player moves
	uint8_t resultNunchuck;
	uint32_t score = 0;
	//uint8_t internalBomblocationX; // TODO remove if useless
	//uint8_t internalBomblocationY; // TODO remove if useless
	float			difficulty = 0.7;
	unsigned long	internalPlayerDropBombTimer; // keeps the time when the bomb is dropped for internalPlayer
	unsigned long	internalBombEffectTimer;
	unsigned long	bombDropped = 0;		// this variable keeps check if a bomb dropped.
	//unsigned long	readyForEffect = 0;		// this variable checks if the bomb animation is ready to be shown.
	unsigned long	doNotDrawPlayer = 0;	// this variables is a timer that stops the redraw of the player for 0.5 sec unless the player moves
	unsigned long	removeSecondTimer = 0;	// this variable is a timer that removes a second a second from the screen timer
	
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
		
		//Serial.print("current view: ");Serial.print(currentView);Serial.print(" Requested view: "); Serial.println(requestedView);
		// check if the the requested view has changed
		if(currentView != requestedView){
			
			currentView = requestedView;
			
			// decide which view to draw
			switch(currentView){
				
				// draw the main menu
				case MENU:
				mainMenu.draw();
				//Serial.println("menu");
				break;
				
				// draw the screen
				case GAME:
				level.drawMap(difficulty);
				internalPlayer.drawPlayer();
				externalPlayer.drawPlayer();
				//Serial.println("spel");
				break;
				
				// draw the highscore screen
				case HIGHSCORE:
				highscore.draw();
				//Serial.println("scores");
				break;
			}
		}
		
		if(currentView == GAME){
			if(millis() >= doNotDrawPlayer + 4100){
				internalPlayer.drawPlayer();
				externalPlayer.drawPlayer();
				doNotDrawPlayer = 0;
			}
			resultNunchuck = SystemFunctions::readNunchuck();
			
			if (resultNunchuck != 0 && resultNunchuck != 5)
			{
				internalPlayer.move(resultNunchuck);

			} else
			
				// check if button Z is pushed(button Z returns value 5)
				if(resultNunchuck == 5 && !bombDropped){
					internalPlayerDropBombTimer = millis();
					doNotDrawPlayer = millis();
					internalBomblocation = internalPlayer.getLocation();
					
					level.updateLevel(internalBomblocation, 4);
					bomb.drawBomb(internalBomblocation);
					bombDropped = 1;
				}
			// check if the bomb is ready to explode
			if(millis() >= internalPlayerDropBombTimer + 3000 && bombDropped && !readyForEffect){
				internalBombEffectTimer = millis();
				score = (bomb.explodeBomb(internalBomblocation) * 10000);
				readyForEffect = 1;
			}
			// check if the effect is ready to be removed
			if(millis() >= internalBombEffectTimer + 500 && readyForEffect == 1){
				bomb.removeAnimation(internalBomblocation);
				//level.updateLevel(internalBomblocation, 2);
				bombDropped = 0;
				readyForEffect = 0;
			}
			level.drawTimer();
			level.updateTimer();
			internalPlayer.updateScore(&score);
			level.drawScore();
		}
		if (currentView == HIGHSCORE)
		{
			highscore.listenToTouchInput();
		}
		
		if (currentView == MENU)
		{
			mainMenu.listenToTouchInput();
		}
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

