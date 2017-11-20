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
	LCD.begin();
	LCD.fillScreen(RGB(0,0,0));
	
	//LCD.drawRect(0,0,310,20,RGB(255,255,0));
	LCD.drawRect(60,40,200,40,RGB(255,255,0)); // box voor Start text
	
	LCD.drawRect(60,120,200,40,RGB(255,255,0));
	int breedte = 315;
	int hoogte = 0;
	int i;
	for(i = 0; i < 10; i++){
		//LCD.drawRect(0,hoogte,breedte,20,RGB(255,255,0));
		breedte ++;
		hoogte += 21;
	}
	Serial.println("Height:");
	Serial.println(LCD.getHeight());
	Serial.println("Width:");
	Serial.println(LCD.getWidth());
} //StartScreen

// default destructor
StartScreen::~StartScreen()
{
} //~StartScreen
