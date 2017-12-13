/*
* Highscore.h
*
* Created: 8-12-2017
* Author: Erwin Jacobs
*/

#include "SystemFunctions.h"
#include "Highscore.h"
//#include <avr/EEPROM.h> 


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
	
	char *nameFirstPlace = malloc(4);
	char *nameSecondPlace = malloc(4);
	char *nameThirdPlace = malloc(4);
	
	strcpy(nameFirstPlace, readName(1));
	//Serial.println(readName(1));
	strcpy(nameSecondPlace, readName(2));
	//Serial.println(nameSecondPlace);
	strcpy(nameThirdPlace, readName(3));
	//Serial.println(nameThirdPlace);
		
	lcdPointer->fillRect(30, 20, 260, 40, RGB(255,255,0));
	lcdPointer->drawText(100, 35, "Highscores", RGB(128,0,128), RGB(255,255,0), 2);
	
	lcdPointer->drawText(60, 80, nameFirstPlace, RGB(255,255,0), RGB(0,0,0),1);
	lcdPointer->drawText(60, 100, nameSecondPlace, RGB(255,255,0), RGB(0,0,0),1);
	lcdPointer->drawText(60, 120, nameThirdPlace, RGB(255,255,0), RGB(0,0,0),1);
	
	
	free(&nameFirstPlace);
	free(&nameSecondPlace);
	free(&nameThirdPlace);
}

char* Highscore::readName(uint8_t place)
{
	char result[0];
	uint8_t r;
	char test;
	place = (place*10)-10;
	uint8_t i;
	for	(i=0; i<=2; i++)
	{
		
		r=eeprom_read_byte((uint8_t*)place+i+1);
		test =(char) r;
		result[i] = test;
		//Serial.println(result[i],HEX);
	}
	Serial.println();
	Serial.println(result);
	return result;
		
}

// default destructor
Highscore::~Highscore()
{
} //~Highscore