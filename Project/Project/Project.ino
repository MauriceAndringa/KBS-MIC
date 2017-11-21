
/*
 * Project.cpp
 *
 * Created: 20-11-2017 11:48:05
 * Author : wsvdy
 */ 

#include <avr/io.h>
#include <MI0283QT9.h>
#include <SD.h>
#include <BMPheader.h>
#include "StartScreen.h"
#include "functions.h"

MI0283QT9 LCD;


int main(void)
{
	init();
	int startPressed = 0, highscorePressed = 0;
	Serial.begin(9600);
	
	//PinSetup
	
	DDRB |= (1<<DDB1);		//Outputpoort van achtergrondlicht
	DDRC &= ~(1<DDC0);		//Inputpoort van potmeter (analogPin0)
	PORTC |= (1<<PORTC0);	//instellen pull-up weerstand
	
	//Startup sequence
	functions FC;
	FC.startTimerScreenBrightness();
	
	// LCD setup
	LCD.begin();
	LCD.fillScreen(RGB(255,255,255));
	LCD.touchStartCal();

	StartScreen SC;
    /* Replace with your application code */
    while (1) 
    {
		FC.screenBrightness();
		if(startPressed && highscorePressed){
			SC.buttonPress(); // kan dit met een interrupt. Op welke port komt de touch signal binnen?
			switch(SC.buttonPress()){
				/*	Debug data
					case 0:
					Serial.println("Hello World");
					break;
				*/
				case 1:
				startPressed = 1;
				break;
				case 2:
				highscorePressed = 1;
			}
		}
		/*	Debug data
			if(startPressed || highscorePressed)
				Serial.println("Eruit");
		*/
    }
}

