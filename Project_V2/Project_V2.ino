/*
* Project_V2.ino
*
* Authors:
*			Erwin
*			Wesley
*/

// INCLUDES
// Libraries
#include <MI0283QT9.h>
#include <Wire.h>
#include <time.h>
#include <SoftwareSerial.h>

// Header Files
#include "SystemFunctions.h"
#include "MainMenu.h"
#include "Map.h"
#include "Player.h"
#include "Bomb.h"
#include "Highscore.h"
#include "EndScreen.h"

// define if the microcontroller is a slave or master
#define IS_SLAVE 0
#define DPLAYER 1
#define DMAP 2
#define START 3

// Global Variables
View currentView	= NONE;
View requestedView	= MENU;

// Objects
MI0283QT9 LCD;
MainMenu mainMenu(&LCD, &requestedView);
Highscore highscore(&LCD, &requestedView);
Bomb bomb(&LCD);
Map level(&LCD, &bomb);
EndScreen endScreen(&LCD, &requestedView);
SoftwareSerial comm(2, 4);


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

//Variables for functions
uint8_t minute = 3;
uint8_t secondTenth = 0;
uint8_t second = 0;
unsigned long readyToRemoveSecondTimer;
uint8_t type, data;
uint16_t datastream;

//Code
int main (void)
{
	// initialize variables
	uint8_t internalBomblocation;
	uint8_t externalBombLocation;
	uint8_t resultNunchuck;
	uint16_t score = 0;
	
	float			difficulty = 0.7;
	unsigned long	internalPlayerDropBombTimer; // keeps the time when the bomb is dropped for internalPlayer
	unsigned long	internalBombEffectTimer;
	unsigned long	bombDropped = 0;			// this variable keeps check if a bomb dropped.
	unsigned long	readyForEffect = 0;			// this variable checks if the bomb animation is ready to be shown.
	unsigned long	doNotDrawPlayer = 0;		// this variables is a timer that stops the redraw of the player for 0.5 sec unless the player moves
	unsigned long	removeSecondTimer = 0;		// this variable is a timer that removes a second a second from the screen timer
	uint8_t tempLoc = 0;
	uint8_t tempVal = 0;
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
		if (comm.available())
		{
			data=comm.read();
			
		}
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
				comm.begin(9600);
				SystemFunctions::drawPercentage(0);
				#if !IS_SLAVE
					while(1){
						//Serial.print(comm.read());
						if(comm.read() == 1){
							comm.write(2);
							//Serial.println("\n\nNicE!\n");
							break;
						}
					}
					level.genBlocks(difficulty);
					while(1){ // wait until Slave is ready to start the game, if not wait here.
						if(comm.read() == START)
							break;
					}
				#else
				//Serial.println("skl;djl;a");
					while(1){
						//Serial.print("Sending");
						comm.write(1);
						if(comm.read() == 2){
							//Serial.println("\n\nNicE!\n")
							break;
						}
					}
					while(1){
						//Serial.print("Waiting");
						SystemFunctions::drawPercentage(tempLoc);
						if(comm.available()){
							tempVal = comm.read();
							while(tempVal == 255)
								tempVal = comm.read();
							//delay(1);
							tempLoc = comm.read();
							while(tempLoc == 255)
								tempLoc = comm.read();
							level.updateLevel(tempLoc, tempVal);
							comm.write(1);
							//Serial.print(tempLoc);Serial.print('\t');Serial.println(tempVal);
						}
						//drawPercentage(tempLoc);
						//Serial.println(tempLoc);
						if(tempLoc >= 142){
							comm.write(START); // send to master that the Slave is ready do start the game.
							break;
						}
					}
				#endif
				level.drawMap();
				internalPlayer.drawPlayer();
				externalPlayer.drawPlayer();
				datastream=0;
				break;
				
				// draw the highscore screen
				case HIGHSCORE:
				highscore.draw();
				break;
				
				// draw the end screen
				case ENDSCREEN:
				endScreen.draw();
			}
		}
		
		
		
		if(currentView == GAME){
			Serial.println(data);

			externalPlayer.setLocation(data);
			
			if(millis() >= doNotDrawPlayer + 4100){
				internalPlayer.drawPlayer();
				externalPlayer.drawPlayer();
				doNotDrawPlayer = 0;
			}
			
			
			resultNunchuck = SystemFunctions::readNunchuck();
			
			if (resultNunchuck != 0 && resultNunchuck != 5)
			{
				internalPlayer.move(resultNunchuck);
				comm.write(internalPlayer.getLocation());
				//TODO: add send function of player loc with internalPlayer.getLocation();
				} else if(resultNunchuck == 5 && !bombDropped){ // check if button Z is pushed(button Z returns value 5)
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
				score = (bomb.explodeBomb(internalBomblocation) * 10);
				readyForEffect = 1;
			}
			// check if the effect is ready to be removed
			if(millis() >= internalBombEffectTimer + 500 && readyForEffect == 1){
				bomb.removeAnimation(internalBomblocation);
				bombDropped = 0;
				readyForEffect = 0;
			}
			
			drawTimer();
			updateTimer();
			internalPlayer.updateScore(&score);
			drawScore();
			if (externalPlayer.lives<=0)
			requestedView = ENDSCREEN;
			if (internalPlayer.lives<=0)
			requestedView = ENDSCREEN;
		}
		
		
		
		
		
		if (currentView == HIGHSCORE)
		{
			highscore.listenToTouchInput();
		}
		
		if (currentView == MENU)
		{
			mainMenu.listenToTouchInput();
		}
		
		if (currentView == ENDSCREEN)
		{
			endScreen.listenToTouchInput();
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



/*
* drawTimer
draws the time on screen is minutes and seconds
* input:  na
* output: na
*/
void drawTimer()
{
	LCD.drawInteger(270, 10, minute, 10, RGB(0,255,0), RGB(0,0,0), 1);
	LCD.drawChar(276,10,':',RGB(0,255,0),RGB(0,0,0),1);
	LCD.drawInteger(284, 10, secondTenth, 10, RGB(0,255,0), RGB(0,0,0), 1);
	LCD.drawInteger(292, 10, second, 10, RGB(0,255,0), RGB(0,0,0), 1);
}

void updateTimer()
{
	if(minute == 0 && secondTenth == 0 && second == 0){
		requestedView = ENDSCREEN;
	}
	
	if(millis() < readyToRemoveSecondTimer + 1000)
	return;
	
	readyToRemoveSecondTimer = millis();
	if(second > 0){
		second--;
		return;
	}
	
	if(secondTenth == 0 && second == 0){
		secondTenth = 5; second = 9;
		minute--;
		return;
	}
	
	if(second == 0){
		second = 9;
		secondTenth --;
		return;
	}
	
	second--;
}

void drawScore()
{
	LCD.drawInteger(290, 45, internalPlayer.getScore(), 10, RGB(255,0,0), RGB(0,0,0), 1);
	LCD.drawInteger(290, 55, internalPlayer.lives, 10, RGB(255,0,0), RGB(0,0,0), 1);
	
	LCD.drawInteger(290, 80, externalPlayer.getScore(), 10, RGB(30,144,255), RGB(0,0,0), 1);
	LCD.drawInteger(290, 90, externalPlayer.lives, 10, RGB(30,144,255), RGB(0,0,0), 1);
}

void drawEndScreen()
{
	int i;
	LCD.fillRect(40, 40, 200, 140, RGB(i,i,i));
	i++;
	while(1);
}
