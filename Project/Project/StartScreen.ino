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
	
	LCD.drawRect(60, 40, 200, 40, RGB(255,255,0)); // box voor Start text
	LCD.drawText(80, 45, "Start", RGB(255,255,0), RGB(0,0,0), 4);
	
	LCD.drawRect(60, 120, 200, 40, RGB(255,255,0)); // box voor highscore text
	LCD.drawText(90, 130, "Highscore", RGB(255,255,0), RGB(0,0,0), 2);
} //StartScreen

// default destructor
StartScreen::~StartScreen()
{
} //~StartScreen
