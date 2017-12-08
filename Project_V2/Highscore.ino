/*
* Highscore.h
*
* Created: 8-12-2017
* Author: Erwin Jacobs
*/

#include "SystemFunctions.h"
#include "Highscore.h"
//#include <EEPROM.h>

// default constructor
Highscore::Highscore(MI0283QT9 *lcdPointer, View *currentViewPointer, View *requestedViewPointer)
{
	Highscore::lcdPointer			= lcdPointer;
	Highscore::currentViewPointer	= currentViewPointer;
	Highscore::requestedViewPointer	= requestedViewPointer;
} //Highscore Screen

void Highscore::draw()
{
	
	// make background black
	lcdPointer->fillScreen(RGB(0,0,0));
	/*
	uint8_t *first = (uint8_t *)malloc(sizeof(uint8_t));
	uint8_t *second = (uint8_t *)malloc(sizeof(uint8_t));
	uint8_t *third = (uint8_t *)malloc(sizeof(uint8_t));
		
	first = eeprom_read_byte(1);
	second = eeprom_read_byte(2);
	third = eeprom_read_byte(3);
	*/
	lcdPointer->fillRect(30, 20, 20, 30, RGB(255,255,0));
	lcdPointer->drawText(125, 30, "Highscores", RGB(128,0,128), RGB(255,255,0), 2);
	/*
	free(first);
	free(second);
	free(third);*/
}

// default destructor
Highscore::~Highscore()
{
} //~Highscore