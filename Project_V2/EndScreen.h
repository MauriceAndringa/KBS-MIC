/* 
* EndScreen.h
*
* Created: 18-12-2017 14:45:35
* Author: wsvdy
*/


#ifndef __ENDSCREEN_H__
#define __ENDSCREEN_H__


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
	
	MI0283QT9	*lcdPointer;

}; //EndScreen

#endif //__ENDSCREEN_H__
