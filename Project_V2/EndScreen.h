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
	EndScreen(MI0283QT9 *lcdPointer);
	~EndScreen();
	
	void draw();
protected:
private:
	EndScreen( const EndScreen &c );
	EndScreen& operator=( const EndScreen &c );
	
	void newHighScore();
	
	MI0283QT9	*lcdPointer;
	
	
	//////////////////////////////////////////////////////////////////////////
	// Debug:
	bool youLose;
	// End debug
	//////////////////////////////////////////////////////////////////////////

}; //EndScreen

#endif //__ENDSCREEN_H__
