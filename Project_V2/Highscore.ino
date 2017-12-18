/*
 * Highscore.ino
 *
 * Authors: 
 *			Erwin
 *			Wesley
 */

#include "SystemFunctions.h"

#include "Highscore.h"


// default constructor
Highscore::Highscore(MI0283QT9 *lcdPointer, View *currentViewPointer, View *requestedViewPointer)
{
	Highscore::lcdPointer			= lcdPointer;
	Highscore::currentViewPointer	= currentViewPointer;
	Highscore::requestedViewPointer	= requestedViewPointer;
} //Highscore Screen

/*
* This function draws the highscore screen with the highscores
*/
void Highscore::draw()
{
	uint8_t i;
	
	// make background black
	lcdPointer->fillScreen(RGB(0,0,0));

	// make header of screen with title
	lcdPointer->fillRect(30, 20, 260, 40, RGB(255,255,0));
	lcdPointer->drawText(60, 35, "Highscores", RGB(128,0,128), RGB(255,255,0), 2);
		
	for (i = 1;i<=3;i++)
	{
		lcdPointer->drawInteger(35, 60+(20*i), i, 10, RGB(255,255,0), RGB(0,0,0),1);		// print ranking
		lcdPointer->drawText(60, 60+(20*i), readName(i), RGB(255,255,0), RGB(0,0,0),1);		// print Name
		lcdPointer->drawText(120, 60+(20*i), readScore(i), RGB(255,255,0), RGB(0,0,0),1);	// print score
	}
	
	free(&i); // free memory space of i
	
}


/*
* This function returns to the main menu when the touchscreen is touched
*/
void Highscore::listenToTouchInput()
{
	
	if(lcdPointer->touchRead()){
		// check if screen is touched
		*requestedViewPointer = MENU;
				
	}
}


/*
* This function reads the EEPROM and returns a 3 character long name 
* input: ranking in list
* returns: 3 character long string
*/
char* Highscore::readName(uint8_t place)
{
	char *result = calloc(4, sizeof(char));
	uint8_t i;				// declaration of needed variables

					
	place = (place*10)-10;	// determine memory location
	
	for	(i=0; i<=2; i++)	// read the 3 characters
	{
		result[i] = (char)eeprom_read_byte((uint8_t*)place+i+1); // save the characters in array
	}
	
	result [4] = NULL;		//end 0
	
	return result;			//return the array
	free(&result);
		
}

/*
* This function reads the EEPROM and returns a 5 character long score
* input: ranking in list
* returns: 5 character long string
*/
char* Highscore::readScore(uint8_t place)
{
	
	char *result = calloc(6, sizeof(char));
	uint16_t i;				// declaration of needed variables
	
	place = (place*10)-7;	// determine memory location
	
	i = (eeprom_read_byte((uint8_t*)place+1)<<8)|(eeprom_read_byte((uint8_t*)place+2)); // combine 2 8bit-bytes into 1 16 bit-byte

	result[0] = (char)(i/10000) + 48;	//turn integer into string
	i = i%10000;
	result[1] = (char)(i/1000)	+ 48;
	i = i%1000;
	result[2] = (char)(i/100)	+ 48;
	i = i%100;
	result[3] =	(char)(i/10)	+ 48;
	i = i%10;
	result[4] = (char) i + 48;
	result[5] = NULL;					//end 0

	
	return result;			//return the array
	free(&result);
	
}



// default destructor
Highscore::~Highscore()
{
} //~Highscore