/* 
* StartScreen.h
*
* Created: 20-11-2017 12:41:33
* Author: wsvdy
*/


#ifndef __STARTSCREEN_H__
#define __STARTSCREEN_H__


class StartScreen
{
//variables
public:
protected:
private:

//functions
public:
	StartScreen();
	~StartScreen();
	int buttonPress();
	void drawScreen();
protected:
private:
	StartScreen( const StartScreen &c );
	StartScreen& operator=( const StartScreen &c );
	
	//uint8_t OpenBMPFile(char *file, int16_t x, int16_t y);

}; //StartScreen

#endif //__STARTSCREEN_H__
