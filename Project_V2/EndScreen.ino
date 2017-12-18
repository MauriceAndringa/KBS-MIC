/* 
* EndScreen.cpp
*
* Created: 18-12-2017 14:45:35
* Author: wsvdy
*/


#include "EndScreen.h"

// default constructor
EndScreen::EndScreen(MI0283QT9 *lcdPointer)
{
	EndScreen::lcdPointer = lcdPointer;
} //EndScreen

void EndScreen::draw()
{
	int i;
	lcdPointer->fillScreen(RGB(255,255,255));
}

// default destructor
EndScreen::~EndScreen()
{
} //~EndScreen
