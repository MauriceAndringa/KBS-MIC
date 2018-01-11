/* 
 * EndScreen.h
 *
 * Authors:
 *			Erwin
 *			Wesley
 */


#ifndef __ENDSCREEN_H__
#define __ENDSCREEN_H__

#include "SystemFunctions.h"

class EndScreen
{
public:
	EndScreen(MI0283QT9 *lcdPointer, View *requestedViewPointer);
	~EndScreen();
	
	void draw();
	void listenToTouchInput();
protected:
private:
	EndScreen( const EndScreen &c );
	EndScreen& operator=( const EndScreen &c );
	
	void newHighScore();
	uint8_t calculatePlayerPlace(uint16_t score);
	void updateHighscore(uint8_t place, Player *player);
	
	MI0283QT9	*lcdPointer;
	View *requestedViewPointer;
	
	uint8_t internalPlayerPlace, externalPlayerPlace, place;
	uint16_t thirdHighscore, secondHighscore, firstHighscore;
	//////////////////////////////////////////////////////////////////////////
	// Debug:
	bool youLose;
	// End debug
	//////////////////////////////////////////////////////////////////////////

}; //EndScreen

#endif //__ENDSCREEN_H__
