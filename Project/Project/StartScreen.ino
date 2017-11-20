/* 
* StartScreen.cpp
*
* Created: 20-11-2017 12:41:33
* Author: wsvdy
*/


#include "StartScreen.h"

// default constructor
StartScreen::StartScreen()
{
	LCD.fillScreen(RGB(0,0,0));
	
	LCD.drawRect(60, 40, 200, 40, RGB(255,255,0)); // box voor Start text
	LCD.drawText(80, 45, "Start", RGB(255,255,0), RGB(0,0,0), 4);
	
	LCD.drawRect(60, 120, 200, 40, RGB(255,255,0)); // box voor highscore text
	LCD.drawText(90, 130, "Highscore", RGB(255,255,0), RGB(0,0,0), 2);
} //StartScreen

int StartScreen::buttonPress()
{
	/*	Debug data
		Serial.print("X: ");
		Serial.println(LCD.touchX());
		Serial.print("Y: ");
		Serial.println(LCD.touchY());
		Serial.println("Hello World");
	*/
	if(!LCD.touchRead())
		return 0;

	if(LCD.touchX() >= 60 && LCD.touchX() <= 260 && LCD.touchY() >= 40 && LCD.touchY() <= 80)
		return 1;

	if(LCD.touchX() >= 60 && LCD.touchX() <= 260 && LCD.touchY() >= 120 && LCD.touchY() <= 160)
		return 2;
		
}


// default destructor
StartScreen::~StartScreen()
{
} //~StartScreen
