/* 
* MainMenu.cpp
*
* Created: 1-12-2017 13:04:02
* Author: wsvdy
*/


#include "MainMenu.h"

// default constructor
MainMenu::MainMenu(MI0283QT9 *lcdPointer, View *currentViewPointer, View *requestedViewPointer)
{
	MainMenu::lcdPointer			= lcdPointer;
	MainMenu::currentViewPointer	= currentViewPointer;
	MainMenu::requestedViewPointer	= requestedViewPointer;
} //MainMenu

void MainMenu::draw()
{
	// make background black
	lcdPointer->fillScreen(RGB(0,0,0));
	
	// draw the buttons on the screen and text
	lcdPointer->fillRect(60, 150, 200, 30, RGB(255,255,0));
	lcdPointer->drawText(125, 160, "Start", RGB(128,0,128), RGB(255,255,0), 2);
	
	lcdPointer->fillRect(60, 200, 200, 30, RGB(255,255,0));
	lcdPointer->drawText(95, 205, "Highscore", RGB(128,0,128), RGB(255,255,0), 2);
}

void MainMenu::listenToTouchInput()
{
	
	if(lcdPointer->touchRead()){
		// check if button is pressed
		if(lcdPointer->touchX() >= 60 && lcdPointer->touchX() <= 260){
		
			// check if button start is pressed
			if(lcdPointer->touchY() >= 150 && lcdPointer->touchY() <= 180){
				
				*requestedViewPointer = GAME;
				
				// check if highscore button is pressed
			} else if(lcdPointer->touchY() >= 200 && lcdPointer->touchY() <= 230){
				
				*requestedViewPointer = HIGHSCORE;
				
			}
		}
	}
}

// default destructor
MainMenu::~MainMenu()
{
} //~MainMenu
