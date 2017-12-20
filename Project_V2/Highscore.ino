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
Highscore::Highscore(MI0283QT9 *lcdPointer, View *requestedViewPointer)
{
	Highscore::lcdPointer			= lcdPointer;
	Highscore::requestedViewPointer	= requestedViewPointer;
} //Highscore Screen

/*
 * draw function draws the highscore screen with the highscores
 * input: nothing
 * output: nothing
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
		lcdPointer->drawText(60, 60+(20*i), SystemFunctions::readName(i), RGB(255,255,0), RGB(0,0,0),1);		// print Name
		lcdPointer->drawText(120, 60+(20*i), SystemFunctions::printScore(i), RGB(255,255,0), RGB(0,0,0),1);	// print score
	}
	
	free(&i); // free memory space of i
	
}


/*
 * listenToTouchInput function returns to the main menu when the touchscreen is touched
 * input: nothing
 * output: nothing
 */
void Highscore::listenToTouchInput()
{
	if(lcdPointer->touchRead()){
		// check if screen is touched
		*requestedViewPointer = MENU;				
	}
}

// default destructor
Highscore::~Highscore()
{
} //~Highscore