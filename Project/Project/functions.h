/* 
* functions.h
*
* Created: 20-11-2017 14:23:43
* Author: Erwin
*/



#ifndef __FUNCTIONS_H__
#define __FUNCTIONS_H__


class functions
{
//variables
public:
protected:
private:

//functions
public:
	functions();
	~functions();
	void startTimerScreenBrightness();
	void screenBrightness();
protected:
private:
	functions( const functions &c );
	functions& operator=( const functions &c );
	int readBrightnessPot();

}; //functions

#endif //__FUNCTIONS_H__
