/*
 * SystemFunctions.h
 *
 * Authors: 
 *			Erwin
 *			Wesley
 */


#ifndef __SYSTEMFUNCTIONS_H__
#define __SYSTEMFUNCTIONS_H__
//#define randomSeed(s) srandom(s)

#include <avr/interrupt.h>
#include <avr/wdt.h>
#include <util/atomic.h>

#define GRID 20

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
	static uint8_t readNunchuck();
	static uint8_t calcX(uint8_t loc);
	static uint8_t calcY(uint8_t loc);
	SystemFunctions();
	~SystemFunctions();

protected:
private:
	static int readAnalog(uint8_t pin);
	static void createRandomSeed();
	static char decodeNunchuck(char x);
	static void sendRequest();

	SystemFunctions( const SystemFunctions &c );
	SystemFunctions& operator=( const SystemFunctions &c );

}; //SystemFunctions

#endif //__SYSTEMFUNCTIONS_H__
