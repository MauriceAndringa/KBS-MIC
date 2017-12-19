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
	youLose = 0;
} //EndScreen

void EndScreen::draw()
{
	lcdPointer->fillScreen(RGB(0,0,0));
	if(youLose)
		lcdPointer->drawText(60,5, "YOU WIN!", RGB(255,255,0), RGB(0,0,0), 3);
	else
		lcdPointer->drawText(60, 5, "YOU LOSE!", RGB(255,255,0), RGB(0,0,0), 3);
	
	lcdPointer->drawText(10, 50, "Your Score was: ", RGB(255,255,0), RGB(0,0,0), 1);
	lcdPointer->drawInteger(130, 50, internalPlayer.getScore(), 10, RGB(255,255,0), RGB(0,0,0), 1);
	
	lcdPointer->drawText(10, 60, "Your enemy's score was: ", RGB(255,255,0), RGB(0,0,0), 1);
	lcdPointer->drawInteger(195, 60, externalPlayer.getScore(), 10, RGB(255,255,0), RGB(0,0,0), 1);
	
	newHighScore();
}

void EndScreen::newHighScore()
{
	Serial.println(SystemFunctions::readScore(3));
	Serial.println(internalPlayer.getScore());
	if(SystemFunctions::readScore(3) > internalPlayer.getScore() && SystemFunctions::readScore(3) > externalPlayer.getScore())
		// check if the scores are below the lowest high score, if so stop the function
		return;
	
	Serial.println(SystemFunctions::readScore(2));
	
	uint8_t internalPlayerPlace = 3, externalPlayerPlace = 3;
	for(int i = 2; i >= 1; i--){
		if(SystemFunctions::readScore(i) < internalPlayer.getScore() && SystemFunctions::readScore(i) > externalPlayer.getScore())
			internalPlayerPlace = i, externalPlayerPlace = i;
		else if(SystemFunctions::readScore(i) < internalPlayer.getScore())
			internalPlayerPlace = i;
		else if (SystemFunctions::readScore(i) < externalPlayer.getScore())
			externalPlayerPlace = i;
	}
	
	if(internalPlayerPlace != externalPlayerPlace){
		Serial.print("Internal player is on "); Serial.print(internalPlayerPlace); Serial.println(" place.");
		Serial.print("External player is on "); Serial.print(externalPlayerPlace); Serial.println(" place.");	
		return;
	}
	
	if(internalPlayer.getScore() > externalPlayer.getScore()){
		Serial.print("Internal player has a higher score, internal player is on ");
		Serial.print(internalPlayerPlace); Serial.print(" place and external player is on ");
		Serial.print(externalPlayerPlace - 1); Serial.println(" place.");
	} else {
		Serial.print("External player has a higher score, external player is on ");
		Serial.print(externalPlayerPlace); Serial.print(" place and internal player is on ");
		Serial.print(internalPlayerPlace - 1); Serial.println(" place.");
	}
	return; 
}

// default destructor
EndScreen::~EndScreen()
{
} //~EndScreen
