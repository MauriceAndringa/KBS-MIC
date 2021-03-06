/*
 * SystemFunctions.h
 *
 * Authors: 
 *			Erwin
 *			Wesley
 */


#ifndef __SYSTEMFUNCTIONS_H__
#define __SYSTEMFUNCTIONS_H__

// libraries
#include <avr/interrupt.h>
#include <avr/wdt.h>
#include <util/atomic.h>

// files
#include "SystemFunctions.h"
#include "Map.h" //TODO check if needed

// Defines
#define NUNCHUCKADRESS 0x52	// nunchuckaddress
#define GRID 20				// grid size in pixels

#define UP 1
#define RIGHT 2
#define DOWN 3
#define LEFT 4
#define SELECT 5 // Declare values for easier understanding of result

// enum for the possible screens
typedef enum{
	MENU,
	GAME,
	HIGHSCORE,
	SETTINGS,
	ENDSCREEN,
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
	static char* readName(uint8_t place);
	static char* printScore(uint8_t place);
	static uint16_t readScore(uint8_t place);
	static void scoreToEEPROM(uint8_t score, uint8_t place);
	static void sendMapData(uint8_t location, uint8_t val);
	static void drawPercentage(uint8_t temploc);
	SystemFunctions();
	~SystemFunctions();

protected:
private:
	static int readAnalog(uint8_t pin);
	static void createRandomSeed();
	static uint8_t decodeNunchuck(uint8_t x);
	static void sendRequest();
	

	SystemFunctions( const SystemFunctions &c );
	SystemFunctions& operator=( const SystemFunctions &c );

}; //SystemFunctions

#endif //__SYSTEMFUNCTIONS_H__
