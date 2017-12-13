/*
 * Highscore.ino
 *
 * Authors: 
 *			Erwin
 *			Wesley
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
	
	// assign memory for name strings
	char *nameFirstPlace = malloc(4);
	char *nameSecondPlace = malloc(4);
	char *nameThirdPlace = malloc(4);
	
	//Save names in strings
	strcpy(nameFirstPlace, readName(1));
	strcpy(nameSecondPlace, readName(2));
	strcpy(nameThirdPlace, readName(3));
	
	// make header of screen with title
	lcdPointer->fillRect(30, 20, 260, 40, RGB(255,255,0));
	lcdPointer->drawText(100, 35, "Highscores", RGB(128,0,128), RGB(255,255,0), 2);
	
	//print rankings
	lcdPointer->drawText(60, 80, nameFirstPlace, RGB(255,255,0), RGB(0,0,0),1);
	lcdPointer->drawText(60, 100, nameSecondPlace, RGB(255,255,0), RGB(0,0,0),1);
	lcdPointer->drawText(60, 120, nameThirdPlace, RGB(255,255,0), RGB(0,0,0),1);
	
	// free assigned memory
	free(&nameFirstPlace);
	free(&nameSecondPlace);
	free(&nameThirdPlace);
}

	/*
	* This function reads the EEPROM and returns a 3 character long name 
	* input: ranking in list
	* returns: 3 character long string
	*/
char* Highscore::readName(uint8_t place)
{
	uint8_t i;				// declaration of needed variables
	char result[0];	
					
	place = (place*10)-10;	// determine memory location
	
	for	(i=0; i<=2; i++)	// read the 3 characters
	{
		result[i] = (char)eeprom_read_byte((uint8_t*)place+i+1); // save the characters in array
	}
	return result;			//return the array
		
}

// default destructor
Highscore::~Highscore()
{
} //~Highscore