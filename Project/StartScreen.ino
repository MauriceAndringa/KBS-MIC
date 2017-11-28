/* 
* StartScreen.cpp
*
* Created: 20-11-2017 12:41:33
* Author: wsvdy
*/

#include "StartScreen.h"
#include "functions.h"

// default constructor
StartScreen::StartScreen()
{
	
} //StartScreen

void StartScreen::drawScreen()
{
	FC.screenBrightness();
	
	// maak het scherm zwart om de 1 pixel rechts en onderin niet ziet
	//LCD.fillScreen(RGB(0,0,0));
	
	// open BMP file en print het op de display
	//BMP.openFile("Sscreen.bmp", 0, 0);
	
	//int i, ii;
	/*for(i = 0; i < 320; i +=10){
		for(ii = 0; ii < 240; i+= 10){
			BMP.openFile("Fire.bmp", i, ii);
		}
	}*/
	//BMP.openFile("Fire.bmp", 0, 0);

	LCD.drawRect(60, 150, 200, 30, RGB(255,255,0)); // box voor Start text
	LCD.fillRect(60, 150, 200, 30, RGB(255,255,0));
	LCD.drawText(125, 160, "Start", RGB(128,0,128), RGB(255,255,0), 2);
	
	LCD.drawRect(60, 200, 200, 30, RGB(255,255,0)); // box voor highscore text
	LCD.fillRect(60, 200, 200, 30, RGB(255,255,0));
	LCD.drawText(95, 205, "Highscore", RGB(128,0,128), RGB(255,255,0), 2);
}

int StartScreen::buttonPress()
{
	/*
	//	Debug data
		Serial.print("X: ");
		Serial.println(LCD.touchX());
		Serial.print("Y: ");
		Serial.println(LCD.touchY());
		i = 0;
	*/
	FC.screenBrightness();
	
	if(!LCD.touchRead())
		return 0;

	if(LCD.touchX() >= 60 && LCD.touchX() <= 260 && LCD.touchY() >= 150 && LCD.touchY() <= 180)
		return 1;

	if(LCD.touchX() >= 60 && LCD.touchX() <= 260 && LCD.touchY() >= 200 && LCD.touchY() <= 230)
		return 2;
		
}

// default destructor
StartScreen::~StartScreen()
{
} //~StartScreen
