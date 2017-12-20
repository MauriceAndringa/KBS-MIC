/* 
* EndScreen.h
*
* Created: 18-12-2017 14:45:35
* Author: wsvdy
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
	
	MI0283QT9	*lcdPointer;
	View *requestedViewPointer;
	
	uint8_t internalPlayerPlace, externalPlayerPlace;
	
	//////////////////////////////////////////////////////////////////////////
	// Debug:
	bool youLose;
	// End debug
	//////////////////////////////////////////////////////////////////////////

}; //EndScreen

#endif //__ENDSCREEN_H__