/* 
 * MainMenu.h
 *
 * Authors:
 *			Erwin
 *			Wesley
 */


#ifndef __MAINMENU_H__
#define __MAINMENU_H__

#include <MI0283QT9.h>


class MainMenu
{
public:
	MainMenu(MI0283QT9 *lcdPointer, View *requestedViewPointer);
	~MainMenu();
	
	void draw();
	void listenToTouchInput();
protected:
private:
	MainMenu( const MainMenu &c );
	MainMenu& operator=( const MainMenu &c );

	MI0283QT9	*lcdPointer;
	View		*requestedViewPointer;

}; //MainMenu

#endif //__MAINMENU_H__
