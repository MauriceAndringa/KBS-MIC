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
	Serial.print("internalPlayer: ");Serial.println(internalPlayer.getScore());
	Serial.print("externalPlayer: ");Serial.println(externalPlayer.getScore());
	
	thirdHighscore = SystemFunctions::readScore(3);
	// check if one or both of the score are higher then the lowest score on the scoreboard
	if(internalPlayer.getScore() > externalPlayer.getScore()){
		if(thirdHighscore > internalPlayer.getScore())
			return;// return and don't write to EEPROM as the internalPlayer has a higher score, but hasn't a higher score then place 3 on scoreboard
	}
	else if(externalPlayer.getScore() > internalPlayer.getScore()){
		if(thirdHighscore > externalPlayer.getScore())
			return; // return and don't write to EEPROM as the externalPlayer has a higher score, but hasn't a higher score then place 3 on scoreboard
	}
	else if(thirdHighscore > internalPlayer.getScore())
		return; // return and don't write to EEPROM as both the internal and external player don't have a high enough score for the scoreboard
	
	// update 
	internalPlayerPlace = calculatePlayerPlace(internalPlayer.getScore());
	updateHighscore(internalPlayerPlace, &internalPlayer);	
	
	externalPlayerPlace = calculatePlayerPlace(externalPlayer.getScore());
	updateHighscore(externalPlayerPlace, &externalPlayer);
	return;
}

/*
 * calculatePlayerPlace function calculates the place of the player
 * input: score of the player
 * returns: place of the player
 */
uint8_t EndScreen::calculatePlayerPlace(uint16_t score)
{
	EndScreen::place = 0;
	for(int i = 3; i >= 1; i--){
		if(SystemFunctions::readScore(i) < score)
			place = i;
	}
	return place;
}

/*
 * updateHigscore updates the highscore
 * input: player place (from calculatePlayerPlace) and pointer to player object
 * returns: na
 */
void EndScreen::updateHighscore(uint8_t place, Player *player)
{
	// return if place is equal to 0
	if(place == 0)
		return;
		
	if(place == 1){
		SystemFunctions::scoreToEEPROM(SystemFunctions::readScore(place + 1), place + 2);
		SystemFunctions::scoreToEEPROM(SystemFunctions::readScore(place), place + 1);
		SystemFunctions::scoreToEEPROM(player->getScore(), place);
	}
	else if(internalPlayerPlace == 2){
		SystemFunctions::scoreToEEPROM(SystemFunctions::readScore(place), place + 1);
		SystemFunctions::scoreToEEPROM(player->getScore(), place);
	}
	else if(internalPlayerPlace == 1)
		SystemFunctions::scoreToEEPROM(player->getScore(), place);
}

// default destructor
EndScreen::~EndScreen()
{
} //~EndScreen
