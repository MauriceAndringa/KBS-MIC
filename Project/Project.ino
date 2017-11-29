
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
//#include <TFT.h>
#include "StartScreen.h"
#include "Functions.h"
#include "GameScreen.h"
#include "OpenBMPFile.h"
#include "OpenBMPFile.h"

#define TEST 0.5
#define EASY 0.7
#define MEDIUM 0.8
/#define HARD 0.9

MI0283QT9 LCD;
StartScreen SC;
GameScreen GC;
Functions FC;
OpenBMPFile BMP;

uint8_t loaded, startPressed, highscorePressed;
float level;

void initSD();

int main(void)
{
	init();
	
	loaded = 0, startPressed = 0, highscorePressed = 0;
	//Serial.begin(9600);
	
	//PinSetup
	
	DDRB |=  (1 <<DDB1);		//Outputpoort van achtergrondlicht
	DDRC &= ~(1 << DDC0);		//Inputpoort van potmeter (analogPin0), en 2 analoge poorten voor het genereren van willerkeurige input.
	PORTC |= (1 <<PORTC0);		//instellen pull-up weerstand
	
	//Startup sequence
	FC.startTimerScreenBrightness();
	
	// LCD setup
	LCD.begin();
	LCD.fillScreen(RGB(255,255,255));

	
	// initialize SD-card
	initSD();
	
	// calibreer de touchscreen
	LCD.touchStartCal();

	//StartScreen SC;
	SC.drawScreen();
	
	//Debug values
	level = TEST;
	

	
	/* Application code */
    while (1) 
    {
		FC.screenBrightness();
		if(!startPressed && !highscorePressed){
			switch(SC.buttonPress()){ // kan dit met een interrupt. Op welke port komt de touch signal binnen?
				//	Debug data
					case 0:
					//Serial.println("no button pressed"); // debug data
					break;
					
				case 1:
					startPressed = 1;
					//Serial.println("Start button pressed"); // debug data
					break;
				case 2:
					//highscorePressed = 1;
					//Serial.println("Highscore button pressed"); // debug data
					break;
			}
		}
		
		
		if(startPressed && !highscorePressed){
			if(!loaded){
				//Serial.println("Start gamescreen");
				GC.drawScreen(level);
				loaded = 1;
				//Serial.println("Geladen");
			}
			GC.terug();
		}
		/*	Debug data
			if(startPressed || highscorePressed)
				Serial.println("Eruit");
		*/
		
    }
}

void initSD() // TODO haal de oneindige loops er uit
{
	uint8_t x;
	x = LCD.drawText(5, 5, "Init SD-card...", RGB(0,0,0), RGB(255,255,255), 1);
	if(!SD.begin(4)){
		LCD.drawText(x, 5 , "failed", RGB(0,0,0), RGB(255,255,255), 1);
		while(1);
	}
	
	if(!SD.exists("Sscreen.bmp")){
		LCD.drawText(x, 5 , "Sscreen.bmp missing", RGB(0,0,0), RGB(255,255,255), 1);
		while(1);
	}
	
	if(!SD.exists("Sblock.bmp")){
		LCD.drawText(x, 5 , "Sblock.bmp missing", RGB(0,0,0), RGB(255,255,255), 1);
		while(1);
	}
	
	if(!SD.exists("Bomb.bmp")){
		LCD.drawText(x, 5 , "bomb.bmp missing", RGB(0,0,0), RGB(255,255,255), 1);
		while(1);
	}
	
	if(!SD.exists("Hblock.bmp")){
		LCD.drawText(x, 5 , "Hblock.bmp missing", RGB(0,0,0), RGB(255,255,255), 1);
		while(1);
	}
	
	if(!SD.exists("Player.bmp")){
		LCD.drawText(x, 5 , "Player.bmp missing", RGB(0,0,0), RGB(255,255,255), 1);
		while(1);
	}
}
