/* 
 * MainMenu.ino
 *
 * Authors:
 *			Erwin
 *			Wesley
 */


#include "MainMenu.h"

// default constructor
MainMenu::MainMenu(MI0283QT9 *lcdPointer, View *requestedViewPointer)
{
	MainMenu::lcdPointer			= lcdPointer;
	MainMenu::requestedViewPointer	= requestedViewPointer;
} //MainMenu

/*
 * draw function draws the main menu screen on the display
 * input: nothing
 * returns: noting
 */
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

/*
 * listenToTouchInput function checks if there is a touch input and it if it's on a button, if so change requested view
 * input: nothing
 * returns: noting
 */
void MainMenu::listenToTouchInput()
{
	
	if(lcdPointer->touchRead()){
		// check if button is pressed
		if(lcdPointer->touchX() >= 60 && lcdPointer->touchX() <= 260){
		
			// check if button start is pressed
			if(lcdPointer->touchY() >= 150 && lcdPointer->touchY() <= 180){
				
				for(int i = 60; i >= 57; i--){
					lcdPointer->drawRect(i, (i + 90), 200, 30, RGB(255,0,0));
				}
				*requestedViewPointer = GAME;
				
				// check if highscore button is pressed
			} else if(lcdPointer->touchY() >= 200 && lcdPointer->touchY() <= 230){
				
				for(int i = 60; i >= 57; i--){
					lcdPointer->drawRect(i, (i + 140), 200, 30, RGB(255,0,0));
				}
				*requestedViewPointer = HIGHSCORE;
				
			}
		}
	}
}

// default destructor
MainMenu::~MainMenu()
{
} //~MainMenu
