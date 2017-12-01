/* 
* MainMenu.h
*
* Created: 1-12-2017 13:04:02
* Author: wsvdy
*/


#ifndef __MAINMENU_H__
#define __MAINMENU_H__

#include <MI0283QT9.h>


class MainMenu
{
//variables
public:
protected:
private:
	MI0283QT9	*lcdPointer;
	View		*currentViewPointer;
	View		*requestedViewPointer;

//functions
public:
	MainMenu(MI0283QT9 *lcdPointer, View *currentViewPointer, View *requestedViewPointer);
	~MainMenu();
	
	void draw();
	void listenToTouchInput();
protected:
private:
	MainMenu( const MainMenu &c );
	MainMenu& operator=( const MainMenu &c );

}; //MainMenu

#endif //__MAINMENU_H__
