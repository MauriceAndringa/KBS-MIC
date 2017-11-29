/* 
* Functions.h
*
* Created: 20-11-2017 14:23:43
* Author: Erwin
*/



#ifndef __FUNCTIONS_H__
#define __FUNCTIONS_H__


class Functions
{
//variables
public:
protected:
private:

//functions
public:
	Functions();
	~Functions();
	void startTimerScreenBrightness();
	void screenBrightness();
	uint8_t readRandom();
protected:
private:
	Functions( const Functions &c );
	Functions& operator=( const Functions &c );
	uint8_t readBrightnessPot();

}; //functions

#endif //__FUNCTIONS_H__
