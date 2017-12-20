/* 
 * EndScreen.ino
 *
 * Authors:
 *			Erwin
 *			Wesley
 */


#include "EndScreen.h"

// default constructor
EndScreen::EndScreen(MI0283QT9 *lcdPointer, View *requestedViewPointer)
{
	EndScreen::lcdPointer = lcdPointer;
	EndScreen::requestedViewPointer	= requestedViewPointer;
	youLose = 0;
	internalPlayerPlace = 0;
	externalPlayerPlace = 0;
} //EndScreen

/*
 * draw function draws the end screen on the display
 * input: nothing
 * returns: noting
 */
void EndScreen::draw()
{
	lcdPointer->fillScreen(RGB(0,0,0));
	if(internalPlayer.getScore() > externalPlayer.getScore())
		lcdPointer->drawText(60,5, "YOU WIN!", RGB(255,255,0), RGB(0,0,0), 3);
	else if(externalPlayer.getScore() > internalPlayer.getScore())
		lcdPointer->drawText(60, 5, "YOU LOSE!", RGB(255,255,0), RGB(0,0,0), 3);
	else
		lcdPointer->drawText(60, 5, "DRAW!", RGB(255,255,0), RGB(0,0,0), 3);

	lcdPointer->drawText(10, 50, "Your Score was: ", RGB(255,255,0), RGB(0,0,0), 1);
	lcdPointer->drawInteger(130, 50, internalPlayer.getScore(), 10, RGB(255,255,0), RGB(0,0,0), 1);
	
	lcdPointer->drawText(10, 60, "Your enemy's score was: ", RGB(255,255,0), RGB(0,0,0), 1);
	lcdPointer->drawInteger(195, 60, externalPlayer.getScore(), 10, RGB(255,255,0), RGB(0,0,0), 1);
	
	newHighScore();
}

/*
 * listenToTouchInput function returns to the main menu when the touchscreen is touched
 * input: nothing
 * returns: noting
 */
void EndScreen::listenToTouchInput()
{	
	if(lcdPointer->touchRead()){
		// check if screen is touched
		*requestedViewPointer = MENU;
	}
}

/*
 * newHighScore function determents if there is a new high score
 * input: nothing
 * returns: noting
 */
void EndScreen::newHighScore()
{
	for(int i = 3; i >= 1; i--){
		if(SystemFunctions::readScore(i) < internalPlayer.getScore() && SystemFunctions::readScore(i) < externalPlayer.getScore())
			internalPlayerPlace = i, externalPlayerPlace = i;
		else if(SystemFunctions::readScore(i) < internalPlayer.getScore())
			internalPlayerPlace = i;
		else if (SystemFunctions::readScore(i) < externalPlayer.getScore())
			externalPlayerPlace = i;
	}

	if(internalPlayerPlace != externalPlayerPlace){
		if(internalPlayerPlace > 0)
			SystemFunctions::scoreToEEPROM(internalPlayer.getScore(), internalPlayerPlace);
		
		if(!externalPlayerPlace > 0)
			SystemFunctions::scoreToEEPROM(externalPlayer.getScore(), externalPlayerPlace);
		return;
	}
	
	if(internalPlayer.getScore() > externalPlayer.getScore()){
		SystemFunctions::scoreToEEPROM(internalPlayer.getScore(), internalPlayerPlace);
		if(externalPlayerPlace + 1 <= 3)
			SystemFunctions::scoreToEEPROM(externalPlayer.getScore(), externalPlayerPlace + 1);
	} else {
		SystemFunctions::scoreToEEPROM(externalPlayer.getScore(), externalPlayerPlace);
		if(internalPlayerPlace + 1 <= 3)
			SystemFunctions::scoreToEEPROM(internalPlayer.getScore(), internalPlayerPlace + 1);
	}
	return;
}

// default destructor
EndScreen::~EndScreen()
{
} //~EndScreen
