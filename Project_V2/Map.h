/* 
* Map.h
*
* Created: 1-12-2017 15:04:12
* Author: wsvdy
*/

#include <time.h>

#include "Bomb.h"



#ifndef __MAP_H__
#define __MAP_H__
#define BLOCK_SIZE 20
#define COLOUR_PILLAR RGB(51, 49, 49)
#define COLOUR_ROAD RGB(91,90,90)
#define COLOUR_DESTROYABLE RGB(64,16,10)
#define COLOUR_GRID RGB(0,0,0)

class Map
{
public:
	Map(MI0283QT9 *lcdPointer, Bomb *bombPointer);
	//Map();
	~Map();
	
	void drawMap(float difficulty);
	void updateChunk(uint8_t loc);
	void updateLevel(uint8_t loc, uint8_t value);
	void drawTimer();
	void updateTimer();
	void drawScore();
	uint8_t checkLocation(uint8_t location);
protected:
private:
	Map( const Map &c );
	Map& operator=( const Map &c );
	MI0283QT9 *lcdPointer;
	Bomb *bombPointer;
	
	//uint8_t calculateArrayLocation(uint8_t x, uint8_t y);
	
	// array level is used to generate a random level
	uint8_t level[143];
	
	uint8_t minute;
	uint8_t secondTenth;
	uint8_t second;
	uint16_t internalPlayerScore;
	uint16_t externalPlayerScore;
	unsigned long readyToRemoveSecondTimer;
	//uint32_t seed;
//int second;
}; //Map

#endif //__MAP_H__
