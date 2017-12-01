/* 
* SystemFunctions.h
*
* Created: 29-11-2017 11:09:18
* Author: Erwin
*/


#ifndef __SYSTEMFUNCTIONS_H__
#define __SYSTEMFUNCTIONS_H__
#define randomSeed(s) srandom(s)

#include <avr/interrupt.h>
#include <avr/wdt.h>
#include <util/atomic.h>

// enum for the possible screens
typedef enum{
	MENU,
	GAME,
	HIGHSCORE,
	SETTINGS,
	NONE	
} View;

class SystemFunctions
{
public:
	static void screenBrightness();
	static uint32_t getRandomSeed();
	SystemFunctions();
	~SystemFunctions();

protected:
private:
	static int readAnalog(uint8_t pin);
	static void createRandomSeed();

	SystemFunctions( const SystemFunctions &c );
	SystemFunctions& operator=( const SystemFunctions &c );

}; //SystemFunctions

#endif //__SYSTEMFUNCTIONS_H__
